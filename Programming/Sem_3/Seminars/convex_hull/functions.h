#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 1
#include "debug.h"

#define DIV_SIZE 8
#define compare(a, b) a < b ? a : b

// Error codes
enum ERRORS{
	ERROR_NO_INPUT_FILES,
	ERROR_BAD_ALLOC
};

// Stack part
// Stack implementation goes here
struct Stack{
	int* stack;
	int* nextItem;

	int stackSize;
	int baseSize;
};

typedef struct Stack* PStack;

void Constructor(PStack);
void Destructor(PStack);

void Push(PStack p, int value);
void Pop(PStack);
void print(PStack);

// Reading file into 2d array
int getNumberOfPoints(FILE*);
int** readStream(FILE*, int);

// Grehem algorithm part
int orientTriangle(int*, int*, int*);
bool isInside(int*, int*, int*);
struct Stack jarvisMarch(int**, int);
double dist(int*, int*);

#endif // FUNCTIONS_H