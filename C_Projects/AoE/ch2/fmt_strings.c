#include <stdio.h>
#include <string.h>

int main(){
	char string[10];
	int A = -73;
	unsigned int B = 31337;

	strcpy(string, "sample");

	printf("[A] Dec: %d, Hex: %x, Pointer: %p, Unsigned Int: %u\n", A, A, A);
	printf("[B] Dec: %d, Hex: %x, Pointer: %p, Unsigned Int: %u\n", B, B, B);
	printf("[field width on B] 3: `%3u`, 10: `%10u`, `%08u`\n", B, B, B);
	printf("[string] %s Address %p\n", string, string);

	// Example of unary address operator (dereferencing) and a %x format string
	printf("variable A is at address %p\n", &A);
	return 0;
}
