#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 100

void lowercase_string(char* str){
	for(int i=0; str[i] != '\0'; i++)
		str[i] = tolower((unsigned char)str[i]);
}

int main(){
	char s_type[BUFFER_SIZE];
	printf("-=-=-=-=-=-=-=-= C Adaptable Server =-=-=-=-=-=-=-=-=-\n");
	printf("UDP or TCP: ");
	if(fgets(s_type, BUFFER_SIZE, stdin) != NULL){
		lowercase_string(s_type);
		printf("[SERVER DEBUG] >>> s_type: %s", s_type);
		if(strcmp(s_type, "udp") == 0)
			printf("UDP\n");
		else if(strcmp(s_type, "tcp") == 0)
			printf("TCP\n");
		else
			printf("Choose UDP or TCP\n");
	}
	
}
