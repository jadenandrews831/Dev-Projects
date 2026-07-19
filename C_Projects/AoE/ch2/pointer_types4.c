#include <stdio.h>

int main() {
	int i;

	char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
	int int_array[5] = {1, 2, 3, 4, 5};

	void *void_ptr;
	void_ptr = (void *)char_array;

	for (i = 0; i < 5; i++){
		printf("[void ptr] is pointing at address %p and contains %c\n", void_ptr, *((char *)void_ptr));
		void_ptr = (void *)((char *)void_ptr) + 1;
	}

	void_ptr = (int*)int_array;

	for(i = 0; i < 5; i++){
		printf("[void ptr] is pointing at address %p and contains %d\n", void_ptr, *((int *)void_ptr));
		void_ptr = (int *)((int *)void_ptr) + 1;
	}

}
