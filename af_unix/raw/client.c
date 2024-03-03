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

    client_fd = socket(AF_UNIX, SOCK_RAW, IPPROTO_ICMP);
    if (client_fd < 0) {
        perror("couldn't create a socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un serv_addr;
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, PATH);

    char buffer[1024];
    socklen_t size = (socklen_t) sizeof(serv_addr);
    while (true)
    {
        gets(buffer);
        if (sendto(client_fd, (char*) buffer, (int) strlen(buffer), MSG_CONFIRM, (struct sockaddr*) &serv_addr, size) < 0) {
            perror("sending data failed");
            exit(EXIT_FAILURE);
        }
        
        if (strstr(buffer, "exit") != NULL)
            break;
    }   
    
    printf("closing the client socket\n");
    close(client_fd);
    return 0;
}