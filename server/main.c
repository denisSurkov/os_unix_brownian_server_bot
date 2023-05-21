#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/un.h>
#include <errno.h>
#include <stdbool.h>

#include "logger.h"

#define SOCKET_NAME "/tmp/test.socket"
#define START_FD_COUNT 20
#define LISTEN_SOCKET_MAX 128
#define MAX_BUFFER_LENGTH 24
#define MAX_RECV_BUFFER_SIZE 14
#define MAX_ANSWER_BUFFER 124

long long SERVER_STATE = 0;


struct ConnectionPool {
    struct pollfd * pollfd;
    char ** buffers;

    unsigned int count;
    size_t size;
};


int getServerListenerSocket()
{
    int listener;
    struct sockaddr_un address;

    unlink(SOCKET_NAME);
    memset(&address, 0, sizeof address);
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, SOCKET_NAME);

    listener = socket(AF_UNIX, SOCK_STREAM, 0);
    if (bind(listener, (struct sockaddr*) &address, sizeof(address)) < 0) {
        writeLog("bind error %s", strerror(errno));
        exit(-1);
    }

    if (listen(listener, LISTEN_SOCKET_MAX) == -1) {
        writeLog("listen error %s", strerror(errno));
        exit(-1);
        return -1;
    }

    writeLog("init listener socket, socket №%d", listener);
    return listener;
}

struct ConnectionPool * initConnectionPool(int listenerFd) {
    struct ConnectionPool * pool = malloc(sizeof(struct ConnectionPool));
    pool->size = START_FD_COUNT;
    pool->pollfd = malloc(sizeof(struct pollfd **) * pool->size);
    pool->buffers = malloc(sizeof(char **) * pool->size);

    pool->pollfd[0].fd = listenerFd;
    pool->pollfd[0].events = POLLIN;

    pool->count = 1;
    return pool;
}


void addToPool(struct ConnectionPool * pool, int clientFd)
{
    if (pool->count == pool->size) {
        pool->size *= 2;

        pool->pollfd = realloc(pool->pollfd, sizeof(*pool->pollfd) * (pool->size));
        pool->buffers = realloc(pool->buffers, sizeof(*pool->buffers) * (pool->size));

        writeLog("increased connection pool size, now %d", pool->size);
    }

    pool->pollfd[pool->count].fd = clientFd;
    pool->pollfd[pool->count].events = POLLIN;
    pool->buffers[pool->count] = malloc(sizeof(char) * MAX_BUFFER_LENGTH);
    memset(pool->buffers[pool->count], 0, MAX_BUFFER_LENGTH);

    pool->count++;
}

void deleteFromPool(struct ConnectionPool * pool, int i)
{
    // Copy the one from the end over this one
    pool->pollfd[i] = pool->pollfd[pool->count-1];

    free(pool->buffers[i]);
    pool->buffers[i] = pool->buffers[pool->count-1];

    pool->pollfd--;
}

size_t recvFromClientToBuffer(struct ConnectionPool * pool, int i) {
    char buf[MAX_RECV_BUFFER_SIZE];
    size_t readBytes = recv(pool->pollfd[i].fd, buf, sizeof buf, 0);
    strncat(pool->buffers[i], buf, readBytes);

    return readBytes;
}


void processNewConnection(int listener, struct ConnectionPool * pool) {
    struct sockaddr_un clientAddress;
    socklen_t addressLen = sizeof clientAddress;

    int clientFd = accept(listener, (struct sockaddr *)&clientAddress, &addressLen);
    if (clientFd == -1) {
        writeLog("accept error %s", strerror(errno));
        return;
    }

    addToPool(pool, clientFd);
    writeLog("new connection socket %d", clientFd);
}


void processZeroBytesReadFromSocket(struct ConnectionPool * pool, int i, size_t readBytes) {
    if (readBytes == 0) {
        writeLog("socket %d disconnected", pool->pollfd[i].fd);
    } else {
        writeLog("recv error with socket %d, error %s", pool->pollfd[i].fd, strerror(errno));
    }

    close(pool->pollfd[i].fd);
    deleteFromPool(pool, i);
}


bool checkIsReadyToUpdateState(const char * buffer) {
    // Делаю предположение, что все клиенты отправляют в конце \n, а после этого ждут ответ.
    // То есть ситуация send("\n213456") невозможна.
    return buffer[strlen(buffer) - 1] == '\n';
}


void updateStateAndSendItToClient(struct ConnectionPool * pool, int i) {
    char resultInput[MAX_BUFFER_LENGTH];
    strcpy(resultInput, pool->buffers[i]);
    resultInput[strlen(resultInput) - 1] = '\0';

    long long res = strtoll(resultInput, NULL, 10);
    writeLog("got %lld from socket %d", res, pool->pollfd[i].fd);

    SERVER_STATE += res;
    writeLog("new server state: %lld", SERVER_STATE);

    char answer[MAX_ANSWER_BUFFER];
    sprintf(answer, "%lld", SERVER_STATE);
    send(pool->pollfd[i].fd, answer, strlen(answer), 0);

    free(pool->buffers[i]);
    pool->buffers[i] = malloc(sizeof(char) * MAX_BUFFER_LENGTH);
    memset(pool->buffers[i], 0, MAX_BUFFER_LENGTH);
}


int main()
{
    initLog(stdout);

    int listener = getServerListenerSocket();
    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        exit(1);
    }

    struct ConnectionPool * pool = initConnectionPool(listener);

    writeLog("init pool, waiting for connections");
    while (1) {
        int poll_count = poll(pool->pollfd, pool->count, -1);
        if (poll_count == -1) {
            writeLog("poll error %s", strerror(errno));
            exit(1);
        }

        for (int i = 0; i < pool->count; i++) {
            if ((pool->pollfd[i].revents & POLLIN) == 0) {
                continue;
            }

            if (pool->pollfd[i].fd == listener) {
                processNewConnection(listener, pool);
                continue;
            }

            size_t readBytes = recvFromClientToBuffer(pool, i);

            if (readBytes <= 0) {
                processZeroBytesReadFromSocket(pool, i, readBytes);
                continue;
            }

            if (!checkIsReadyToUpdateState(pool->buffers[i])) {
                continue;
            }

            updateStateAndSendItToClient(pool, i);
        }
    }

    return 0;
}
