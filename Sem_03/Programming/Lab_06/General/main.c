#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lcs.h"

const char min_letter = 'A';
const char max_letter = 'Z';

char* GenerateRandomSequence(int sequence_length) {
	char* sequence = (char*) malloc(sizeof(char) * (sequence_length + 1));
	srand(time(NULL));

	for (int i = 0; i < sequence_length; ++i) {
		sequence[i] = rand() % (max_letter + 1 - min_letter) + min_letter;
	}

	sequence[sequence_length] = '\0';

	return sequence;
}

int main() {
	// char* X = GenerateRandomSequence(20);
	// char* Y = GenerateRandomSequence(10);

	char* X = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
	char* Y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
	
	LCS* lcs = LCS_Length(X, Y);

	for (int i = 0; i <= lcs->height; ++i) {
		for (int j = 0; j <= lcs->width; ++j) {
			fprintf(stdout, "%d ", lcs->matrix[i][j]);
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");

	for (int i = 1; i <= lcs->height; ++i) {
		for (int j = 1; j <= lcs->width; ++j) {
			fprintf(stdout, "%c ", lcs->symbols[i][j]);
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");

	PrintLCS(lcs, X, lcs->height, lcs->width);
	fprintf(stdout, "\n");

	// free(X);
	// free(Y);

	Destructor(lcs);

	return 0;
}