#include <stdio.h>

#include "matrix.h"
#include "gauss.h"

int main(const int argc, const char* argv[]) {
	FILE* f = fopen(argv[1], "r");
	Matrix* m = ScanMatrix(f);
	if (m == NULL) {
		fprintf(stderr, "main: Matrix read is failed.\n");
		return 0;
	}

	Matrix* result = Constructor(get_height_matrix(m), 1);

	if (result == NULL) {
		fprintf(stderr, "main: Result matrix creating is failed\n");
		return 0;
	}

	int result_code;
	if (!(result_code = SolveGauss(m, result))) {
		if (get_height_matrix(result)) {
			PrintMatrix(stdout, result);
		} else {
			printf("There aren't any solutions.\n");
		}
	} else {
		fprintf(stderr, "main: Solving equation by Gauss method is failed\n");
	}

	Destructor(result);
	Destructor(m);
	fclose(f);

	return result_code;
}