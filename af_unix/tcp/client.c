#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/un.h>

#define PATH "tpf_unix_sock.bin"


int main() {
    int client_fd;
    int ret;

    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
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

    struct sockaddr_un serv_addr;
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, PATH);

    ret = connect(client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        perror("couldn't connet to server: ");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (true)
    {
        gets(buffer);
        if (send(client_fd, buffer, strlen(buffer), 1024) < 0) {
            perror("sending data failed\n");
            exit(EXIT_FAILURE);
        }
        
        if (strstr(buffer, "exit") != NULL)
            break;
    }   
    
    printf("closing the client socket\n");
    close(client_fd);
    return 0;
}