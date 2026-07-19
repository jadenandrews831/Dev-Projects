#include <stdio.h>

int main() {
	char message[] = "Hello, world!";
	int count, i;

	printf("Repeat how many times: ");
	scanf("%d", &count);

	for(i=0; i < count; i++) 
		printf("%3d - %s\n", i, message);
}
