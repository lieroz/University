//
// Created by lieroz on 04.12.16.
//

#include "Helpers.h"

void ScanInput(char* buffer, size_t size, const char* name, bool is_null) {
	fprintf(stdout, "Enter %s: ", name);
	getline(&buffer, &size, stdin);
	buffer[strlen(buffer) - 1] = '\0';

	if (!is_null) {

		while (strlen(buffer) == 0) {
			fprintf(stdout, "Enter %s: ", name);
			getline(&buffer, &size, stdin);
			buffer[strlen(buffer) - 1] = '\0';
		}
	}
}