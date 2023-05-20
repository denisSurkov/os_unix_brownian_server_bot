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

int SERVER_STATE = 0;


int get_listener_socket(void)
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

void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    if (*fd_count == *fd_size) {
        *fd_size *= 2;

        *pfds = realloc(*pfds, sizeof(**pfds) * (*fd_size));
    }

    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN; // Check ready-to-read

    (*fd_count)++;
}

void del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    // Copy the one from the end over this one
    pfds[i] = pfds[*fd_count-1];

    (*fd_count)--;
}

void process_new_connection(int listener, struct pollfd *pfds[], int *fd_count, int *fd_size) {
    struct sockaddr_un remoteaddr;
    socklen_t addrlen = sizeof remoteaddr;
    int newfd = accept(listener,
                       (struct sockaddr *)&remoteaddr,
                       &addrlen);

    if (newfd == -1) {
        perror("accept");
    } else {
        add_to_pfds(pfds, newfd, fd_count, fd_size);

        printf("pollserver: new connection %s "
               "socket %d\n", remoteaddr.sun_path, newfd);
    }
}


int main(void)
{
    int listener = get_listener_socket();

    int fd_count = 0;
    int fd_size = START_FD_COUNT;
    struct pollfd *pfds = malloc(sizeof *pfds * fd_size);

    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        exit(1);
    }

    pfds[0].fd = listener;
    pfds[0].events = POLLIN;

    fd_count = 1;

    while (1) {
        int poll_count = poll(pfds, fd_count, -1);

        if (poll_count == -1) {
            perror("poll");
            exit(1);
        }

        for(int i = 0; i < fd_count; i++) {
            if (pfds[i].revents & POLLIN) {
                if (pfds[i].fd == listener) {
                    process_new_connection(listener, &pfds, &fd_count, &fd_size);
                } else {
                    char buf[256];
                    size_t readBytes = recv(pfds[i].fd, buf, sizeof buf, 0);

                    int sender_fd = pfds[i].fd;

                    if (readBytes <= 0) {
                        if (readBytes == 0) {
                            printf("pollserver: socket %d hung up\n", sender_fd);
                        } else {
                            perror("recv");
                        }

                        close(pfds[i].fd);
                        del_from_pfds(pfds, i, &fd_count);
                    } else {
                        int res = atoi(buf);
                        printf("%d", res);
                        SERVER_STATE += res;
                        printf("%d", SERVER_STATE);
                    }

                    for (int j = 0; j < 256; ++j) {
                        buf[j] = '\0';
                    }
                }
            }
        }
    }

    return 0;
}
