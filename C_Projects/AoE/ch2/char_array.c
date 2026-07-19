#include <stdio.h>

int main(){
	char s[] = "Hello, World!";
	printf("%s\n", s);
	s[5] = 0;					// a null byte ends a character array (string).
	printf("%s\n", s);				// adding one here terminates the string at 'Hello'.
	return 0;
}
