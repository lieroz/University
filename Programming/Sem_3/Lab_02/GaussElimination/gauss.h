#ifndef __GAUSS_H__
#define __GAUSS_H__

#include <stdio.h>

#include "matrix.h"

// solves a equation system by Gauss method
// if solution completed returns 0
// if the system has not any solution result size is 0
int SolveGauss(Matrix* a, Matrix* result);

#endif // __GAUSS_H__