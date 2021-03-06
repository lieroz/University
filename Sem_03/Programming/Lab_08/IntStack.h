#ifndef __INTSTACK_H_DEF__
#define __INTSTACK_H_DEF__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MULTIPLIER_COEF 2
#define compare(a, b) a < b ? a : b

// Stack part
// Stack implementation goes here
typedef struct {
	int* base;
	int* next_item;

	int stack_size;
	int base_size;
} IntStack;

IntStack* constructor();
void destructor(IntStack*);

void push(IntStack*, int);
int pop(IntStack*);
void printStack(IntStack*);

int top(IntStack*);
int size(IntStack*);
bool empty(IntStack*);

#endif // __INTSTACK_H_DEF__