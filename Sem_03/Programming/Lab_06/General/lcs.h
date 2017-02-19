#ifndef __LCS_H_DEF__
#define __LCS_H_DEF__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int height;
	int width;

	int** matrix;
	char** symbols;
} LCS;

void Destructor(LCS*);
LCS* LCS_Length(char*, char*);
void PrintLCS(LCS*, char*, int, int);

#endif // __LCS_H_DEF__