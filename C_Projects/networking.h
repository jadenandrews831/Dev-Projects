#include <errno.h>
#include <string.h>

#define TYPESIZE 4
#define IPSIZE 17
#define BUFFERSIZE 4096

int fatal(char* str, int e){
    printf("[SERVER ERROR] >>> %s\n\tError: %s\n", str, strerror(e));
    exit(-1);
}

void lowercase_str(char* str){
	for(int i=0; str[i] != '\0'; i++)
		str[i] = (unsigned char)tolower(str[i]);
}

