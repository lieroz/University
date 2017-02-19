#ifndef __CSTACK_H_DEF__
#define __CSTACK_H_DEF__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MULTIPLIER_COEF 2
#define compare(a, b) a < b ? a : b

// Stack part
// Stack implementation goes here
typedef struct {
	char* base;
	char* next_item;

	int stack_size;
	int base_size;
} CStack;

CStack* Constructor();
void Destructor(CStack*);

void Push(CStack*, char);
char Pop(CStack*);
void PrintStack(CStack*);

char top(CStack*);
int size(CStack*);
bool is_empty(CStack*);

#endif // __CSTACK_H_DEF__