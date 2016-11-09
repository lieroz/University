#include <stdio.h>

#include "hamming_distance.h"

int main(const int argc, const char** argv) {
	if (argc != 2) {
		fprintf(stderr, "ERROR: NO INPUT DATA!!!\n");
		return 0;
	}

	FILE* f = fopen(argv[1], "r");

	if (!f) {
		fprintf(stderr, "ERROR: INVALID ARGUMENT!!!\n");
		return 0;
	}

	ReadFromStream(f);

	fclose(f);

	return 0;
}