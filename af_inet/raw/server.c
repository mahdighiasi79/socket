#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <string.h>


int main() {
    int ret;
    int server_fd;
    int new_socket;

    server_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (server_fd < 0) {
        perror("couldn't create a socket: ");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    ret = inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
    if (ret < 0) {
        perror("invalid IP address: ");
        exit(EXIT_FAILURE);
    }
    address.sin_port = htons(8081);
    socklen_t addrlen = sizeof(address);

    ret = bind(server_fd, (struct sockaddr*) &address, sizeof(address));
    if (ret < 0) {
        perror("couldn't bind the socket to the desired IP and port: ");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    socklen_t size = (socklen_t) sizeof(address);
    int len_message;
    while (true)
    {
        recvfrom(server_fd, buffer, sizeof(buffer), 0, NULL, NULL);
        puts(buffer);
    }

    printf("closing server socket\n");
    close(server_fd);
    return 0;
}