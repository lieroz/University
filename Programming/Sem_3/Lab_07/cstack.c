#include "cstack.h"

// Stack part
// Constructors & destructors in C manner
CStack* Constructor() {
	CStack* stack = (CStack*) malloc(sizeof(CStack));

	stack->base = NULL;
	stack->next_item = NULL;
	stack->stack_size = 0;
	stack->base_size = 0;

	return stack;
}

void Destructor(CStack* stack) {
	free(stack->base);

	stack->base = NULL;
	stack->next_item = NULL;
	stack->stack_size = 0;
	stack->base_size = 0;

	free(stack);
}

// ------------------------------------------------------------------------
// Stack build methods, usually declared private
void copy(const char* from, char* to, int count) {
	const char* f_ptr = from;
	char* t_ptr = to;

	for (int i = 0; i < count; ++i) {
		*(t_ptr + i) = *(f_ptr + i);
	}
}

void resize(CStack* stack, int new_size) {
	char* new_base = (char*) malloc(sizeof(char) * new_size);
	int size_to_copy = compare(stack->stack_size, new_size);

	if (stack->base && new_base) {
		copy(stack->base, new_base, size_to_copy);
	}

	free(stack->base);

	stack->base = new_base;
	stack->base_size = new_size;
}

void reserve(CStack* stack, int size) {
	int diff = stack->base_size - size;

	if (diff <= 0) {
		resize(stack, size * MULTIPLIER_COEF);
		stack->next_item = stack->base + size;
	} else {
		stack->next_item += size - stack->stack_size;
	}

	stack->stack_size = size;
}

// Stack public methods
void Push(CStack* stack, char value) {
	reserve(stack, stack->stack_size + 1);
	*(stack->next_item - 1) = value;
}

char Pop(CStack* stack) {
	if (is_empty(stack)) {
		return -1;
	}

	char result = *(stack->next_item - 1);
	reserve(stack, stack->stack_size - 1);

	return result;
}

void PrintStack(CStack* stack) {
	for (int i = 0; i < stack->stack_size; ++i) {
		fprintf(stdout, "%c", stack->base[i]);
	}
	fprintf(stdout, "\n");
}

char top(CStack* stack) {
	return *(stack->next_item - 1);
}

int size(CStack* stack) {
	return stack->stack_size;
}

bool is_empty(CStack* stack) {
	return stack->stack_size == 0;
}