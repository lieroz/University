#include <stdio.h>

#include "matrix.h"
#include "iterations.h"

#define WRONG_NUMBER_OF_ARGUMENTS 0

int main(const int argc, const char* argv[]) {
	if (argc < 2) {
		fprintf(stderr, "ERROR: WRONG_NUMBER_OF_ARGUMENTS!!!\n");
		return WRONG_NUMBER_OF_ARGUMENTS;
	}

	FILE* f = fopen(argv[1], "r");

	if (!f) {
		fprintf(stderr, "ERROR: BAD_ALLOC!!!\n");
		return BAD_ALLOC;
	}

	Matrix* matrix = ReadFromStream(f);
	fprintf(stdout, "/********Basic matrix:********/\n");
	PrintMatrix(matrix);

	double* result = Iterations(matrix);
	for (int i = 0; i < matrix->height; ++i) {
		fprintf(stdout, "%7.3lf\n", result[i]);
	}

	Destructor(matrix);
	free(result);
	fclose(f);

	return 0;
}
