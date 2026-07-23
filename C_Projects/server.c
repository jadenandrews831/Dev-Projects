#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "networking.h"

int udp_server(){
	int sock_fd;
	char host[IPSIZE];
	char garb[8];
	void *buffer;
	unsigned int port;
	char client_ip[IPSIZE];
	unsigned int client_port;
	unsigned int *s_len;

	struct sockaddr_in server_addr;
	struct sockaddr_storage sender_addr;
	struct sockaddr_in* s;
	socklen_t sender_len = (socklen_t)sizeof(sender_addr);

	sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock_fd != -1){

		printf("[SERVER DEBUG] >>> Successfully Created Socket File Descriptor\n");
		printf("Port: ");
		scanf("%s", garb);
		while(strncmp(garb, "\n", 1) == 0){
			scanf("%s", garb);
		}
		port = atoi(garb);
		printf("[SERVER DEBUG] >>> Port: %d\n", port);

		memset(&server_addr, '\0', sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port);
		server_addr.sin_addr.s_addr = 0;

	} else {
		printf("[SERVER DEBUG] >>> Failed to create Socket File Descriptor");
		return -1;
	}
	if(bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) != -1){
		printf("[SERVER DEBUG] >>> Successfully Bound Socket\n");
		buffer = malloc(BUFFERSIZE);
		if (sizeof(buffer) > 0){
			printf("[SERVER DEBUG] >>> Successfully allocated %d bytes for the buffer at %p!\n", BUFFERSIZE, buffer);
		} else {
			printf("[SERVER ERROR] >>>in udp_server()<< while allocating buffer.\nError %s\n", strerror((int)errno));
			close(sock_fd);
			return -1;
		}
		while(1){
			s_len = (unsigned int *)&sender_len;
			if(recvfrom(sock_fd, buffer, BUFFERSIZE, 0, (struct sockaddr *)&sender_addr, s_len) != -1){
				printf("[SERVER DEBUG] >>> Successfully received data!\nData >>> %s\n", (char *)buffer);
			} else {
				printf("[SERVER ERROR] >>>in udp_server()<<< while receiving data\nBuffer: %p\nBufferSize: %d\nError: %s", buffer, BUFFERSIZE, strerror((int)errno));
				close(sock_fd);
				return -1;
			}
			if(sender_addr.ss_family == AF_INET){
				s = (struct sockaddr_in *)&sender_addr;
				inet_ntop(AF_INET, &s->sin_addr, client_ip, sizeof(client_ip));
				client_port = ntohs(s->sin_port);
				printf("[SERVER DEBUG] >>> Client Host: %s\tClient Port: %u\n", client_ip, client_port);
			}
			strcpy(buffer, (char *)buffer);
			if(sendto(sock_fd, buffer, BUFFERSIZE, 0, (struct sockaddr *)&sender_addr, (unsigned int)(*s_len)) >= 0){
				printf("[SERVER DEBUG] >>> Message successfully sent to >>>%p<<<\n\n", &s->sin_addr);
			} else {
				printf("[SERVER ERROR] >>>in udp_server()<<< while sending data back to client >>>%s:%d<<<", client_ip, client_port);
			}
		}
	} else {
		printf("[SERVER ERROR] >>>in udp_server()<<< while binding socket to host\nError Message: %s\n", strerror((int)errno));
		close(sock_fd);
		return -1;
	}
	return 0;
}

int choose_type(char* s_type){
	if(strcmp(s_type, "tcp") == 0){
		printf("[SERVER DEBUG] >>> s_type: %s\n", s_type);
		return 1;
	}
	else if (strcmp(s_type, "udp") == 0){
		printf("[SERVER DEBUG] >>> s_type: %s\n", s_type);
		if(udp_server() != -1){
			printf("[SERVER DEBUG] >>>in choose_type()<<< udp_server() call successful!\n");
		}
		return 2;
	}
	else{
		printf("Please type UDP or TCP\n");
		return -1;
	}
}

int main(){
	char s_type[TYPESIZE];
	printf("-=-=-=-=-=-=-=-= C Adaptable Server =-=-=-=-=-=-=-=-\n");
	printf("UDP or TCP: ");
	if(fgets(s_type, TYPESIZE, stdin) != NULL){
		lowercase_str(s_type);
		choose_type(s_type);
	}

}
