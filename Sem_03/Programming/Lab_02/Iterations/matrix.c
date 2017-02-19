//
// Created by lieroz on 30.09.16.
//

#include "matrix.h"

Matrix* Constructor() {
	Matrix* m = (Matrix*) malloc(sizeof(Matrix));

	m->height = 0;
	m->width = 0;
	m->data = NULL;

	return m;
}

void Destructor(Matrix* m) {
	for (int i = 0; i < m->height; ++i) {
		free(m->data[i]);
	}
	free(m->data);

	m->height = 0;
	m->width = 0;
	m->data = NULL;
}

void ScanMatrix(FILE* input_stream, Matrix* m) {
	int height = m->height;
	int width = m->width;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (fscanf(input_stream, "%lf", &m->data[i][j]) != 1) {
				fprintf(stderr, "INVALID ARGUMENT!\n");
				return;
			}
		}
	}
}

Matrix* ReadFromStream(FILE* input_stream) {
	int height = 1;
	if (fscanf(input_stream, "%d", &height) != 1) {
		fprintf(stderr, "INVALID ARGUMENT!\n");
		return INVALID_ARGUMENT;
	}
	int width = height + 1;

	Matrix* m = Constructor();
	m->height = height;
	m->width = width;

	double** data = (double**) malloc(sizeof(double*) * height);
	if (!data) {
		fprintf(stderr, "BAD MEMORY ALLOCATION!\n");
		return BAD_ALLOC;
	}

	for (int i = 0; i < height; ++i) {
		data[i] = (double*) malloc(sizeof(double) * width);
		if (!data[i]) {
			fprintf(stderr, "BAD MEMORY ALLOCATION!\n");
			return BAD_ALLOC;
		}
	}

	m->data = data;
	ScanMatrix(input_stream, m);

	return m;
}

//int GetRowSum(double* row, int size, int index) {
//	int sum = 0;
//	for (int i = 0; i < size; ++i) {
//		if (i != index) {
//			sum += row[i];
//		}
//	}
//
//	return sum;
//}
//
//bool IsDominant(double* row, int size, int index) {
//	if (row[index] >= GetRowSum(row, size, index)) {
//		return true;
//	}
//	return false;
//}
//
//void Subtraction(int size, double* a, double* b) {
//	for (int i = 0; i < size + 1; ++i) {
//		a[i] -= b[i];
//	}
//}
//
//void Addition(int size, double* a, double* b) {
//	for (int i = 0; i < size + 1; ++i) {
//		a[i] += b[i];
//	}
//}
//
//Matrix* MatrixConversion(Matrix* m) {
//	Matrix* conv_matrix = Constructor();
//
//	int height = conv_matrix->height = m->height;
//	conv_matrix->width = m->width;
//	double** data = m->data;
//
//	for (int i = 0; i < height; ++i) {
//		while (true) {
//			if (IsDominant(data[i], height, i)) {
//				break;
//			}
//
//			int rand_element = rand() % height;
//			while (rand_element == i) {
//				rand_element = rand() % height;
//			}
//
//			int operation = rand() % 2;
//			if (operation == 0) {
//				Subtraction(height, data[i], data[rand_element]);
//			} else {
//				Addition(height, data[i], data[rand_element]);
//			}
//		}
//	}
//
//	conv_matrix->data = data;
//
//	return conv_matrix;
//}

void PrintMatrix(Matrix* m) {
	int height = m->height;
	int width = m->width;
	double** data = m->data;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (j < height) {
				fprintf(stdout, "%7.3lf ", data[i][j]);
			} else {
				fprintf(stdout, "|%7.3lf ", data[i][j]);
			}
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
}
