#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <errno.h>

#include "../common/logger.h"
#include "../common/config_reading.h"

#define MAX_RECV_BUFFER_LENGTH 24
#define MAX_BYTE_INTERVAL 256
#define DEFAULT_SLEEP_MSECS 300

void checkArguments(int argc, char * argv[]) {
    if (argc < 2) {
        printf("usage: %s /path/to/config/ -t time_to_sleep\n", argv[0]);
        exit(-1);
    }
}

int getTimeToSleep(int argc, char * argv[]) {
    int timeToSleepMsecs = DEFAULT_SLEEP_MSECS;

    int timeToSleepArgument = getopt(argc, argv, "t:");
    if (timeToSleepArgument == 't') {
        timeToSleepMsecs = (int) strtol(optarg, NULL, 10);
    }

    return timeToSleepMsecs;
}

unsigned short getRandomByteToAddSleep() {
    srand(time(NULL));
    return (unsigned short) rand() % MAX_BYTE_INTERVAL;
}


int msleep(long msec) {
    // https://stackoverflow.com/a/1157217
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

int connectToServer(const char * serverName) {
    int serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un serverSocketAddr;
    memset(&serverSocketAddr, 1, sizeof(struct sockaddr_un));

    serverSocketAddr.sun_family = AF_UNIX;
    strcpy(serverSocketAddr.sun_path, serverName);

    if (connect(serverSocket, (struct sockaddr *) &serverSocketAddr, sizeof(serverSocketAddr)) < 0) {
        perror("connect");
        exit(-1);
    }

    return serverSocket;
}


int main(int argc, char * argv[]) {
    checkArguments(argc, argv);

    initLog(stdout);

    const char * configName = argv[1];
    const char * socketName = getSocketNameFromConfig(configName);

    int serverSocket = connectToServer(socketName);

    unsigned short randomByteToSleep = getRandomByteToAddSleep();
    unsigned short byteRead = 0;
    int timeToSleep = getTimeToSleep(argc, argv);

    writeLog("client start sending data");
    char stdinBuffer;
    while (fread(&stdinBuffer, 1, 1, stdin) > 0) {
        if (byteRead < randomByteToSleep) {
            byteRead++;

            if (byteRead == randomByteToSleep) {
                msleep(timeToSleep);
            }
            writeLog("slept before sending");
        }

        size_t bytesSend = send(serverSocket, (const char *) &stdinBuffer, 1, 0);
        writeLog("send %d bytes", bytesSend);

        if (stdinBuffer == '\n') {
            char recvBuffer[MAX_RECV_BUFFER_LENGTH];
            size_t bytesRecv = recv(serverSocket, recvBuffer, MAX_RECV_BUFFER_LENGTH, 0);
            recvBuffer[bytesRecv] = '\0';
            writeLog("recv %d bytes, %s", bytesRecv, recvBuffer);
        }
    }

    writeLog("client send all data");
    return 0;
}
