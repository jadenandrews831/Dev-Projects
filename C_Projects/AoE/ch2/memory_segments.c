#include <stdio.h>
#include <stdlib.h>

int global_var;

int global_initialized = 5;

void function() {
	int stack_var;
	printf("the function's stack_var is at address %p\n", &stack_var);
}

int main() {
	int stack_var;
	static int static_initialized_var = 5;
	static int static_var;
	int *heap_var_ptr;

	heap_var_ptr = (int *) malloc(4);

	printf("global_initialized is at address %p\n", &global_initialized);
	printf("static_initialized_var is at address %p\n", &static_initialized_var);
	printf("static_var is at address %p\n", &static_var);
	printf("global_var is at address %p\n", &global_var);
	printf("heap_var_ptr points to address %p\n", heap_var_ptr);
	printf("stack_var is at address %p\n", &stack_var);
	function();
}
