#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define DEBUG 1
#include "debug.h"

typedef double type;

enum ERRORS{
	ERROR_NO_INPUT_FILES,
	ERROR_BAD_ALLOC
};

bool checkConvexity(FILE*);
type getArea(FILE*, bool);

#endif // FUNCTIONS_H
