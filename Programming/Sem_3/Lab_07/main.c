#include <stdio.h>

#include "cstack.h"
#include "state_machine.h"

int main(const int argc, const char** argv) {

	if (argc < 2) {
		fprintf(stderr, "ERROR: NO INPUT FILE!!!\n");
		return 0;
	} else if (argc == 2) {
		FILE* f = fopen (argv[1], "r");

		fprintf(stdout, "<Table_of_tokens>\n");

		if (!f) {
			fprintf(stderr, "ERROR: WRONG FILE!!!\n");
			return 0;
		}

		ReadFromStream(f, stdout);
		fprintf(stdout, "</Table_of_tokens>\n");

		fclose(f);
	} else if (argc == 3) {
		FILE* in = fopen(argv[1], "r");
		FILE* out = fopen(argv[2], "w");

		fprintf(out, "<?xml version='1.0' encoding='utf-8'?>\n");
		fprintf(out, "<Table_of_tokens>\n");

		if (!in || !out) {
			fprintf(stderr, "ERROR: WRONG FILE!!!\n");
			return 0;
		}

		ReadFromStream(in, out);
		fprintf(out, "</Table_of_tokens>\n");

		fclose(out);
		fclose(in);
	} else {
		fprintf(stderr, "ERROR: WRONG NUMBER OF PARAMETERS!!!\n");
		return 0;
	}

	return 0;
}
