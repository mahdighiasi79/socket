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

    server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server_fd < 0) {
        perror("couldn't create a socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    ret = inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
    if (ret < 0) {
        perror("invalid IP address");
        exit(EXIT_FAILURE);
    }
    address.sin_port = htons(8081);
    socklen_t addrlen = sizeof(address);

    ret = bind(server_fd, (struct sockaddr*) &address, sizeof(address));
    if (ret < 0) {
        perror("couldn't bind the socket to the desired IP and port");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    socklen_t size = (socklen_t) sizeof(address);
    int len_message;
    while (true)
    {
        len_message = (int) recvfrom(server_fd, (char*) buffer, 1024, MSG_WAITALL, (struct sockaddr*) &address, &size);
        if (len_message < 0) {
            perror("recieving data failed");
            exit(EXIT_FAILURE);
        } 
        
        for (int i = 0; i < len_message; i++)
            printf("%c", buffer[i]);
        printf("\n");

        if (strstr(buffer, "exit") != NULL)
            break;
    }

    printf("closing the server socket\n");
    close(server_fd);
    return 0;
}