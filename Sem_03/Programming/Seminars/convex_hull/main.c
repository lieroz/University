#include "functions.h"

int main(const int argc, const char** argv){
	enum ERRORS error;

	if (argc < 2){
		fprintf(stderr, "Error!!! No input files!\n");
		error = ERROR_NO_INPUT_FILES;
		return error;
	}

	FILE* f = fopen(argv[1], "r");

	if (!f){
		fprintf(stderr, "Error!!! Can't read file!\n");
		error = ERROR_BAD_ALLOC;
		return error;
	}
	
	int numberOfPoints = getNumberOfPoints(f);
	int** field = readStream(f, numberOfPoints);
	fclose(f);

	struct Stack stack = jarvisMarch(field, numberOfPoints);

	// Calculating perimeter of hull
	double Perimiter;
	for (int i = 0; i < numberOfPoints; ++i){
		Perimiter += dist(field[stack.stack[i]], field[stack.stack[i + 1]]);
	}
	fprintf(stdout, "The minimum perimeter of hull is: %lf\n", Perimiter);

	// Freeing memory
	for (int i = 0; i < numberOfPoints; ++i)
		free(field[i]);
	free(field);

	Destructor(&stack);
	return 0;
}