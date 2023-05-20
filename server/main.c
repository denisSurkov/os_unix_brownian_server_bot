#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/un.h>

#define SOCKET_NAME "/tmp/test.socket"
#define START_FD_COUNT 20
#define LISTEN_SOCKET_MAX 128
#define MAX_BUFFER_LENGTH 24

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
        perror("bind error");
        exit(-1);
    }

    if (listen(listener, LISTEN_SOCKET_MAX) == -1) {
        return -1;
    }

    return listener;
}

void addToPool(struct ConnectionPool * pool, int clientFd)
{
    if (pool->count == pool->size) {
        pool->size *= 2;

        pool->pollfd = realloc(pool->pollfd, sizeof(*pool->pollfd) * (pool->size));
        pool->buffers = realloc(pool->buffers, sizeof(*pool->buffers) * (pool->size));
    }

    pool->pollfd[pool->count].fd = clientFd;
    pool->pollfd[pool->count].events = POLLIN;
    pool->buffers[pool->count] = malloc(sizeof(char *) * MAX_BUFFER_LENGTH);

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

void processNewConnection(int listener, struct ConnectionPool * pool) {
    struct sockaddr_un clientAddress;
    socklen_t addressLen = sizeof clientAddress;

    int clientFd = accept(listener, (struct sockaddr *)&clientAddress, &addressLen);
    if (clientFd == -1) {
        perror("accept");
        return;
    }

    addToPool(pool, clientFd);
    printf("pollserver: new connection socket %d\n", clientFd);
}


int main(void)
{
    int listener = getServerListenerSocket();
    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        exit(1);
    }


    struct ConnectionPool * pool = malloc(sizeof(struct ConnectionPool));
    pool->count = 1;
    pool->size = START_FD_COUNT;
    pool->pollfd = malloc(sizeof(struct pollfd **) * pool->size);
    pool->buffers = malloc(sizeof(char **) * pool->size);

    pool->pollfd[0].fd = listener;
    pool->pollfd[0].events = POLLIN;

    while (1) {
        int poll_count = poll(pool->pollfd, pool->count, -1);

        if (poll_count == -1) {
            perror("poll");
            exit(1);
        }

        for (int i = 0; i < pool->count; i++) {
            if ((pool->pollfd[i].revents & POLLIN) == 0) {
                continue;
            }

            if (pool->pollfd[i].fd == listener) {
                processNewConnection(listener, pool);
            } else {
                char buf[24];
                int sender_fd = pool->pollfd[i].fd;
                size_t readBytes = recv(sender_fd, buf, sizeof buf, 0);
                strncat(pool->buffers[i], buf, readBytes);

                if (readBytes <= 0) {
                    if (readBytes == 0) {
                        printf("pollserver: socket %d hung up\n", sender_fd);
                    } else {
                        perror("recv");
                    }

                    close(pool->pollfd[i].fd);
                    deleteFromPool(pool, i);
                } else {
                    if (pool->buffers[i][strlen(pool->buffers[i]) - 1] == '\n') {
                        long long res = strtoll(buf, NULL, 10);

                        printf("%d\n", res);
                        SERVER_STATE += res;
                        printf("%lld\n", SERVER_STATE);

                        char answer[128];
                        sprintf(answer, "%lld", SERVER_STATE);

                        send(pool->pollfd[i].fd, answer, strlen(answer), 0);

                        free(pool->buffers[i]);
                        pool->buffers[i] = malloc(sizeof(char *) * MAX_BUFFER_LENGTH);
                    }
                }
            }
        }
    }

    return 0;
}
