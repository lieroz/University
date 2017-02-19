//
// Created by lieroz on 01.10.16.
//

#include "iterations.h"
#include "matrix.h"

void FreeData(double* a, double* b, double* c, double* d) {
	free(a);
	free(b);
	free(c);
	free(d);
}

double* Iterations(Matrix* m){
	int height = m->height;
	int width = m->width;
	double** data = m->data;

	double buf_c;

	double* curr_x = (double*) malloc(sizeof(double) * height);
	double* prev_x = (double*) malloc(sizeof(double) * height);
	double* temp_x = (double*) malloc(sizeof(double) * height);
	double* buf_row = (double*) malloc(sizeof(double) * (width));

	for (int i = 0; i < height; i++) {
		curr_x[i] = 0;
		prev_x[i] = 0;
		temp_x[i] = 0;
	}

	int max_k = 0;
	fprintf(stdout ,"Enter max number of iterations: ");

	if ((fscanf(stdin ,"%d", &max_k) != 1) || (max_k <= 0)){
		fprintf(stderr, "ERROR: INVALID_ARGUMENT!!!\n");
		FreeData(curr_x, prev_x, temp_x, buf_row);
		return INVALID_ARGUMENT;
	}

	double epsilon = 0;
	fprintf(stdout ,"Enter precision: ");

	if ((fscanf(stdin ,"%lf", &epsilon) != 1) || (epsilon <= 0)){
		fprintf(stderr, "ERROR: INVALID_ARGUMENT!!!\n");
		FreeData(curr_x, prev_x, temp_x, buf_row);
		return INVALID_ARGUMENT;
	}

	for (int i = 0; i < height; i++){
		buf_c = data[i][i];
		for (int j = 0; j < (width); j++){

			if (i == j) {
				data[i][j] = 0;
			}
			else {
				data[i][j] /= -buf_c;
			}
			if (j == height) {
				data[i][j] *= -1;
			}
		}
	}

	fprintf(stdout, "\n/********Reduced matrix********/\n");
	PrintMatrix(m);

	double euclid_norm = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			euclid_norm += data[i][j] * data[i][j];
		}
	}
	euclid_norm = sqrt(euclid_norm);

	if (euclid_norm > 1) {
		fprintf(stderr, "ERROR: INVALID_MATRIX!!!\n");
		FreeData(curr_x, prev_x, temp_x, buf_row);
		return INVALID_MATRIX;
	}

	double sum = 0;
	int k = 0, max;

	for (int i = 0; i < height; i++) {
		prev_x[i] = data[i][height];
	}


	do {
		k++;
		if (k != 1) {
			for (int i = 0; i < height; i++) {
				prev_x[i] = curr_x[i];
			}
		}

		for (int i = 0; i < height; i++) {
			sum = 0;
			for (int j = 0; j < height; j++) {
				sum += prev_x[j] * data[i][j];
			}

			curr_x[i] = sum + data[i][height];
		}

		max = 0;
		for (int i = 0; i < height - 1; i++) {
			if (abs(curr_x[max] - prev_x[max]) < abs(curr_x[i + 1] - prev_x[i + 1])) {
				max = i + 1;
			}
		}

	} while ((abs(curr_x[max] - prev_x[max]) < epsilon) && (k < max_k));

	free(buf_row);
	free(prev_x);
	free(temp_x);

	return curr_x;
}