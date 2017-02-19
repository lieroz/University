#include <stdio.h>
#include "prettytable.h"

int main(const int argc, const char** argv){
	enum ERRORS error;

	if (argc < 2){
		fprintf(stderr, "No input files!!!\n");
		error = FILE_NOT_FOUND;
		return error;
	}

	FILE* f = fopen(argv[1], "r");

	if (!f){
		fprintf(stderr, "Error opening file!!!\n");
		error = ERROR_OPENING_FILE;
		return error;
	}

	printTable(f);
	fclose(f);

	return 0;
}
