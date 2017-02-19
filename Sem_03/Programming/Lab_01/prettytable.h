#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum ERRORS{
	FILE_NOT_FOUND,
	ERROR_OPENING_FILE
};

int getStrCount(void*);
int getColCount(void*);
int* getColWidths(void*);
void printTable(void*);

#endif // FUNCTIONS_H
