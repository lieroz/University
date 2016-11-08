#include <stdio.h>
#include <stdbool.h>
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

	bool convex = checkConvexity(f);

	if (!convex){
		fprintf(stdout, "Convex || self-intersecting polygon: FALSE\n\n");
		rewind(f);

		double area = getArea(f, true);
		fprintf(stdout, "The area of nonconvex polygon is: %lf\n", area);
	} else{
		fprintf(stdout, "Convex || self-intersecting polygon: TRUE\n\n");
	}

	fclose(f);

	return 0;
}
