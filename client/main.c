#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_NAME "/tmp/test.socket"


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

    char buffer[10];
    strcpy(buffer, "0\n");
    send(serverSocket, buffer, sizeof(buffer), 0);
    perror("send");
    printf("%s", buffer);

    recv(serverSocket, buffer, 10, 0);
    printf("%s", buffer);

    printf("Hello, World!\n");
    return 0;
}
