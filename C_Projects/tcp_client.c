#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "networking.h"

int client_handler(char* host, char* port){
    int sock_fd;
    struct sockaddr_in sock;

    if((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        fatal(">>>in client_handler()<<< while creating socket file descriptor", errno);
}

int main(){
    char host[HOSTSIZE];
    char port_str[8];
    unsigned int port;
    printf("-=-=-=-=-=-=-=-= C TCP Client =-=-=-=-=-=-=-=-\n");
    printf("Remote Host: ");
    if(fgets(host, HOSTSIZE, stdin) == NULL)
        fatal(">>>in main()<<< while getting Host from STDIN", errno);

    printf("Remote Port: ");
    if(scanf("%d", &port) < 0)
        fatal(">>>in main()<<< while getting Port from STDIN", errno);

    snprintf(port_str, sizeof(port_str), "%d", port);
    printf("[CLIENT DEBUG] >>> PORT: %d\tPORT_STR: %s\n", port, port_str);

    if(client_handler(host, port_str) == -1)
        fatal(">>>in main()<<< after returning from client_handler() [SOMETHING WENT WRONG :(]")

    
}