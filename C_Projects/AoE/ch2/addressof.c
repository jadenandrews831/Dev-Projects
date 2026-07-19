#include <stdio.h>

int main(){
	int i = 5;
	int *int_ptr;

	int_ptr = &i;

	printf("i: %d\nAddress of i: %p\nint_ptr: %p\n", i, &i, int_ptr);
	return 0;
}
