#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "networking.h"

struct sockaddr_in sock;
unsigned int sock_len = sizeof(sock);
struct addrinfo hints, *res;
void *buffer;

int client_loop(int, int, char *, char *);

int udp_client(char* host, char* port){
    int sock_fd, status = 0;
    char garb = '\n';
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    while(1) client_loop(sock_fd, status, host, port);
}

int client_loop(int sock_fd, int status, char *host, char *port){
    if((status = getaddrinfo(host, port, &hints, &res)) != 0)
        fatal(">>>in udp_client()<<< while adding address to sockadd_in structure", errno);
    printf("[CLIENT DEBUG] >>> Successfully added address to sockadd_in structure\n");
    memcpy(&sock, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);

    if((sock_fd = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
        fatal(">>>in udp_client()<<< while creating client socket file descriptor", errno);

    printf("[CLIENT DEBUG] >>> Successfully created socket file descriptor!\n");

    buffer = malloc(BUFFERSIZE);
    printf("C_UDPClient> ");
    if(fgets((char *)buffer, BUFFERSIZE, stdin) == NULL)
        fatal(">>in udp_client()<< while getting user data from stdin", errno);

    if(sendto(sock_fd, buffer, BUFFERSIZE, 0, (struct sockaddr*)&sock, sock_len) == -1)
        fatal(">>>in udp_client()<<< while sending data to udp server", errno);

    memset(buffer, 0, BUFFERSIZE);
    
    if(recvfrom(sock_fd, buffer, BUFFERSIZE, 0, (struct sockaddr *)&sock, &sock_len) == -1)
        fatal(">>>in udp_client()<<< while receiving data from udp server", errno);
    printf("[CLIENT DEBUG] >>> Successfully obtained data from udp server!\n");
    printf("[MESSAGE FROM SERVER] >>> %s\n", (char *)buffer);
}

int main(){
    char host[17];
    unsigned int port;
    char *port_str;

    printf("-=-=-=-=-=-=-=-= C UDP Client =-=-=-=-=-=-=-=-\n");
    
    printf("Remote Host: ");
    if(fgets(host, IPSIZE, stdin) == NULL)
        fatal(">>>in main()<<< while getting remote host from stdin\n", errno);
    host[strcspn(host, "\n")] = '\0';
    printf("[CLIENT DEBUG] >>> Host: %s\n", host);

    printf("Remote Port: ");
    if(scanf("%u", &port) < 0)
        fatal(">>>in main()<<< while getting remote port from stdin\n", errno);
    printf("[CLIENT DEBUG] >>> Port: %u\n", port);

    port_str = malloc(8);
    if(snprintf(port_str, 8, "%u", port) < 0)
        fatal(">>>in main()<<< while converting port to a string\n", errno);

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    udp_client(host, port_str);
    
}