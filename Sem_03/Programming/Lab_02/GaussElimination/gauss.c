#include "gauss.h"

// retuns stepped matrix (a) rank
// if include_right_column == 0 the last
// column will bo ignored
int CalcRankOfSteppedMatrix(Matrix* a, int include_right_column) {
	int height = get_height_matrix(a);
	int width = get_width_matrix(a) - !include_right_column;
	double** data = get_data_matrix(a);

	int rank = height;
	for (int i = height - 1; i >= 0; --i, --rank) {
		int have_nonzero = 0;
		for (int j = 0; j < width; ++j) {
			if ((have_nonzero = data[i][j])) {
				break;
			}
		}

		if (have_nonzero) {
			break;
		}
	}

	return rank;
}

// solves a equation system by Gauss method
// if solution completed returns 0
// if the system has not any solution result size is 0
int SolveGauss(Matrix* a, Matrix* result) {
	int a_height = get_height_matrix(a);
	int a_width = get_width_matrix(a);

	if (a_height + 1 != a_width) {
		fprintf(stderr, "SolveGauss: unsupported matrix (a) size: %dx%d", a_height, a_width);
		return -1;
	}

	ToSteppedFormMatrix(a);

	int rank = CalcRankOfSteppedMatrix(a, 1);

	// if system has a solution(s)
	if (rank == CalcRankOfSteppedMatrix(a, 0)) {
		SetSizeMatrix(result, a_height, 1);

		double** a_data = get_data_matrix(a);
		double** x_data = get_data_matrix(result);

		// defaults values for freedom variables
		for (int i = rank; i < a_height; ++i) {
			// we can assign any value
			// for exapmle, 0
			x_data[i][0] = 0;
		}

		// variables count
		int n = a_height;

		for (int i = rank - 1; i >= 0; --i) {
			// index of the first non-zero factor in the row
			int curr_var = -1;
			for (int j = i; 1; ++j) {
				if (a_data[i][j]) {
					curr_var = j;
					break;
				}
			}

			// calculating result
			double temp = 0;
			for (int j = curr_var + 1; j < n; ++j) {
				temp += a_data[i][j] * x_data[j][0];
			}
			x_data[curr_var][0] = (a_data[i][n] - temp) / a_data[i][curr_var];
		}
	} else {
		SetSizeMatrix(result, 0, 0);
	}

	return 0;
}