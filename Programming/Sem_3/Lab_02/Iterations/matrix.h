//
// Created by lieroz on 30.09.16.
//

#ifndef ITERATIONS_MATRIX_H
#define ITERATIONS_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define INVALID_ARGUMENT 0
#define BAD_ALLOC        0
#define INVALID_MATRIX   0

typedef struct {
	int height;
	int width;

	double** data;
} Matrix;

// Constructor & destructor in C-manner
Matrix* Constructor();
void Destructor(Matrix*);

// Reading matrix from stream
void ScanMatrix(FILE*, Matrix*);
Matrix* ReadFromStream(FILE*);

// Normalizing matrix for iteration method
//Matrix* MatrixConversion(Matrix*);

// Printing matrix
void PrintMatrix(Matrix*);

#endif // ITERATIONS_MATRIX_H
