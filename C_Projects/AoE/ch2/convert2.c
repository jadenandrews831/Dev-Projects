#include <stdio.h>
#include <stdlib.h>


int usage(char *program_name){
	printf("Usage: %s <message> < # of times to repeat \>", program_name);
	exit(1);
}

int main(int argc, char* argv[]){
	// if (argc < 3) usage(argv[0]);
	
	int repeat = atoi(argv[2]);
	printf("[DEBUG] >> repeat: %d\n", repeat);
	printf("Printing %d times\n", repeat);

	//if (repeat > 0){
		for (int i = 0; i < repeat; i++){
			printf("%s\n", argv[1]);
		}
	//}
	return 0;
}
