#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <errno.h>

#define SOCKET_NAME "/tmp/test.socket"

int msleep(long msec)
{
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

int main() {
    int serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un serverSocketAddr;
    memset(&serverSocketAddr, 1, sizeof(struct sockaddr_un));

    serverSocketAddr.sun_family = AF_UNIX;
    strcpy(serverSocketAddr.sun_path, SOCKET_NAME);

    int ok = connect(serverSocket, (struct sockaddr *) &serverSocketAddr, sizeof(serverSocketAddr));
    if (ok < 0) {
        perror("connect");
        exit(-1);
    }
    srand(time(NULL));

    unsigned short r = rand() % 200;
    printf("%d", r);
    unsigned int byteRead = 0;
    char stdinBuffer;
    while (fread(&stdinBuffer, 1, 1, stdin) > 0) {
        byteRead++;
        if (byteRead == r) {
            msleep(300);
        }
        send(serverSocket, (const char *) &stdinBuffer, 1, 0);
        perror("send");

        if (stdinBuffer == '\n') {
            char buffer[24];
            recv(serverSocket, buffer, 10, 0);
            printf("%s", buffer);
            exit(-1);
        }
    }

    printf("Hello, World!\n");
    return 0;
}
