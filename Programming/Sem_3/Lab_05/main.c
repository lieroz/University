#include <stdio.h>

#include "check_string.h"

int main(const int argc, const char** argv) {
	if (argc != 2) {
		fprintf(stderr, "ERROR: NO INPUT FILES!!!\n");
		return 0;
	}
	
	FILE* f = fopen(argv[1], "r");

	CheckNumbers(f);

	fclose(f);

	return 0;
}