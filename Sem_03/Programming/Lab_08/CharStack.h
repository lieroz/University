#ifndef __CharStack_H_DEF__
#define __CharStack_H_DEF__

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
} CharStack;

CharStack* Constructor();
void Destructor(CharStack*);

void Push(CharStack*, char);
char Pop(CharStack*);
void PrintStack(CharStack*);

char Top(CharStack*);
int Size(CharStack*);
bool Empty(CharStack*);

#endif // __CharStack_H_DEF__