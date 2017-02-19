#include "functions.h"

// Stack part
// Constructors & destructors in C manner
void Constructor(PStack p){
	p->stack = NULL;
	p->nextItem = NULL;
	p->stackSize = 0;
	p->baseSize = 0;
}

void Destructor(PStack p){
	free(p->stack);

	p->stack = NULL;
	p->nextItem = NULL;
	p->stackSize = 0;
	p->baseSize = 0;
}

// ------------------------------------------------------------------------
// Stack build methods, usually declared private
// DO NOT PLAY WITH THIS
// PLEASE!!!
void copy(const int* from, int* to, int count){
	const int* fPtr = from;
	int* tPtr = to;
	for (int i = 0; i < count; ++i){
		*(tPtr + i) = *(fPtr + i);
	}
}

void resize(PStack p, int newSize){
	int* newStack = (int*)malloc(sizeof(int) * newSize);
	int sizeToCopy = compare(p->stackSize, newSize);

	if (p->stack && newStack)
		copy(p->stack, newStack, sizeToCopy);

	free(p->stack);

	p->stack = newStack;
	p->baseSize = newSize;
}

void reserve(PStack p, int size){
	int diff = p->baseSize - size;

	if (diff <= 0 || diff > DIV_SIZE){
		resize(p, size + DIV_SIZE);
		p->nextItem = p->stack + size;
	} else{
		p->nextItem += size - p->stackSize;
	}

	p->stackSize = size;
}

// Stack public methods
void Push(PStack p, int value){
	reserve(p, p->stackSize + 1);
	*(p->nextItem - 1) = value;
}

void Pop(PStack p){
	int result = *(p->nextItem - 1);
	reserve(p, p->stackSize - 1);
}

void print(PStack p){
	for (int i = 0; i < p->stackSize; ++i){
		fprintf(stdout, "%d ", p->stack[i]);
	}
	fprintf(stdout, "\n");
}

// ------------------------------------------------------------------------
// Reading file into 2d array
int getNumberOfPoints(FILE* f){
	int numberOfPoints = 0;
	while (!feof(f)){
		if (fgetc(f) == '\n') numberOfPoints++;
	}

	return numberOfPoints;
}

int** readStream(FILE* f, int numberOfPoints){
	int** field = malloc(sizeof(int*) * numberOfPoints);
	for (int i = 0; i < numberOfPoints; ++i){
		field[i] = malloc(sizeof(int) * 2);
	}

	rewind(f);

	for (int i = 0; i < numberOfPoints; ++i){
		fscanf(f, "%d%d", &field[i][0], &field[i][1]);
		PDEBUG("x, y : (%d, %d);\n", field[i][0], field[i][1]);
	}

	fprintf(stdout, "\n");

	return field;
}

// ------------------------------------------------------------------------
// Grehem algorithm part
int orientTriangle(int* A, int* B, int* C){
	return A[0] * (B[1] - C[1]) + B[0] * (C[1] - A[1]) + C[0] * (A[1] - B[1]);
}

bool isInside(int* A, int* B, int* C){
	return (A[0] <= B[0] && B[0] <= C[0] && A[1] <= B[1] && B[1] <= C[1]);
}

struct Stack jarvisMarch(int** field, int numberOfPoints){
	int base = 0;
	for (int i = 1; i < numberOfPoints; ++i){
		if (field[i][1] < field[base][1]){
			base = i;
		} else{
			if ((field[i][1] == field[base][1]) && field[i][0] < field[base][0]){
				base = i;
			}
		}
	}

	struct Stack S;
	Constructor(&S);
	Push(&S, base);
	PDEBUG("Stack: %d\n", S.stack[0]);

	int first = base;
	int cur = base;

	do{
		int next = (cur + 1) % numberOfPoints;
		for (int i = 0; i < numberOfPoints; ++i){
			int sign = orientTriangle(field[cur], field[next], field[i]);

			if (sign < 0){
				next = i;
			} else if (sign == 0){
				if (isInside(field[cur], field[next], field[i])){
					next = i;
				}
			}
		}
		cur = next;
		Push(&S, next);

		ZDEBUG;
		print(&S);

	} while (cur != first);

	fprintf(stdout, "\n");
	
	return S;
}

double dist(int* A, int* B){
	return sqrt((A[0] - B[0]) * (A[0] - B[0]) + (A[1] - B[1]) * (A[1] - B[1]));
}