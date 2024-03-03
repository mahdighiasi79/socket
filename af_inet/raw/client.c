#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


int main() {
    int client_fd;
    int ret;
    char buffer[1024] = "ping";

    client_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (client_fd < 0) {
        perror("couldn't create a socket: ");
        exit(EXIT_FAILURE);
    }

    // struct sockaddr_in clnt_addr;
    // clnt_addr.sin_family = AF_INET;
    // clnt_addr.sin_port = htons(8082);
    // ret = inet_pton(AF_INET, "127.0.0.1", &clnt_addr.sin_addr);
    // if (ret < 0) {
    //     perror("invalid IP address: ");
    //     exit(EXIT_FAILURE);
    // }

    // ret = bind(client_fd, (struct sockaddr*) &clnt_addr, sizeof(clnt_addr));
    // if (ret < 0) {
    //     perror("couldn't bind the socket to the desired IP and port: ");
    //     exit(EXIT_FAILURE);
    // }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8081);
    ret = inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    if (ret < 0) {
        perror("invalid IP address: ");
        exit(EXIT_FAILURE);
    }

    socklen_t size = (socklen_t) sizeof(serv_addr);
    while (true)
    {
        gets(buffer);

        /*the third input argument in the "sendto()" function must be the maximum length of the buffer
        not the length of the message we want to send*/
        sendto(client_fd, buffer, 1024, 0, (struct sockaddr*) &serv_addr, size);
    }   
    
    printf("closing client socket\n");
    close(client_fd);
    return 0;
}