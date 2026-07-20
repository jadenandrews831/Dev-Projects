#include <stdio.h>

void s_input(char *s, size_t s_size){
	printf("What would you like to say: ");
	fgets(s, s_size, stdin);
	printf("\nYou said:\n[User Statement] >>> %s", s);
}

int main(){
	char s_data[100];
	s_input(s_data, sizeof(s_data));
}
