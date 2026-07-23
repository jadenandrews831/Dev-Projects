#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include "networking.h"

int tcp_client(char* host, char* port){
    int sock_fd;
    int status;
    int buf_len;
    void *buffer;
    struct sockaddr_in sock;

    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if((status = getaddrinfo(host, port, &hints, &res)) != 0)
        fatal(">>>in tcp_client()<<< while creating getaddrinfo structure\n", errno);
    memcpy(&sock, res->ai_addr, res->ai_addrlen);
    printf("[CLIENT DEBUG] >>> Host: %u\tPort: %u\n", sock.sin_addr.s_addr, sock.sin_port);

    if((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        fatal(">>>in tcp_client()<<< while creating socket file descriptor", errno);

    if(connect(sock_fd, (struct sockaddr *)&sock, sizeof(sock)) != 0)
        fatal(">>>in tcp_client()<<< while connecting socket to remote host", errno);
    printf("[CLIENT DEBUG] >>> Successfully connected to >>>%s:%s<<<\n", host, port);

    while (1){

        printf("TCPClientC> ");
        buffer = malloc(BUFFERSIZE);
        if(fgets(buffer, BUFFERSIZE, stdin) == NULL)
            fatal(">>>in tcp_client()<<< while fetching buffer data from stdin", errno);

        buf_len = strlen(buffer);
        if(send(sock_fd, buffer, buf_len, 0) == -1)
            fatal(">>>in tcp_client()<<< while sending data to remote host", errno);
        printf("[CLIENT DEBUG] >>> Successfully send data to remote host\n");

        memset(buffer, 0, BUFFERSIZE);
        if(recv(sock_fd, buffer, BUFFERSIZE, 0) == -1)
            fatal(">>>in tcp_client()<<< while receiving data from remote host", errno);
        printf("[CLIENT DEBUG] >>> Successfully retrieved data from remote host\n");

        printf("[MESSAGE FROM SERVER] >>> %s\n", (char *)buffer);
    }
    return 0;
}

int main(){
    char host[HOSTSIZE];
    char port_str[8];
    unsigned int port;
    printf("-=-=-=-=-=-=-=-= C TCP Client =-=-=-=-=-=-=-=-\n");
    printf("Remote Host: ");
    if(fgets(host, HOSTSIZE, stdin) == NULL)
        fatal(">>>in main()<<< while getting Host from STDIN", errno);
    host[strcspn(host, "\n")] = '\0';

    printf("Remote Port: ");
    if(scanf("%d", &port) < 0)
        fatal(">>>in main()<<< while getting Port from STDIN", errno);

    snprintf(port_str, sizeof(port_str), "%d", port);
    printf("[CLIENT DEBUG] >>> PORT: %d\tPORT_STR: %s\n", port, port_str);

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    if(tcp_client(host, port_str) == -1)
        fatal(">>>in main()<<< after returning from client_handler() [SOMETHING WENT WRONG :(]", errno);

    
}