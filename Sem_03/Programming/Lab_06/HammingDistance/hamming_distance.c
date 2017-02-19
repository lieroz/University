#include "hamming_distance.h"

DNA_Matrix* Constructor(int amount, int sequence_size) {
	DNA_Matrix* dna = (DNA_Matrix*) malloc(sizeof(DNA_Matrix));

	char** data = (char**) malloc(sizeof(char*) * amount);
	for (int i = 0; i < amount; ++i) {
		data[i] = (char*) malloc(sizeof(char) * (sequence_size + 1));
	}

	dna->sequences = data;
	dna->amount_of_sequences = amount;
	dna->sequence_symbol_count = sequence_size;

	return dna;
}

void Destructor(DNA_Matrix* dna) {
	for (int i = 0; i < dna->amount_of_sequences; ++i) {
		free(dna->sequences[i]);
	}
	free(dna->sequences);

	dna->sequences = NULL;
	dna->amount_of_sequences = 0;
	dna->sequence_symbol_count = 0;

	free(dna);
	dna = NULL;
}

char* SeekCommonElements(DNA_Matrix* dna) {
	char* most_common_symbols = (char*) malloc(sizeof(char) * (dna->sequence_symbol_count + 1));

	for (int i = 0; i < dna->sequence_symbol_count; ++i) {
		int most_common_symbol_count = 0;
		char smallest_character = 'Z';

		for (int j = 0; j < dna->amount_of_sequences; ++j) {
			int count = 1;

			for (int k = j + 1; k < dna->amount_of_sequences; ++k) {

				if (dna->sequences[j][i] == dna->sequences[k][i]) {
					++count;
				}
			}

			if (count > most_common_symbol_count) {
				most_common_symbol_count = count;
				most_common_symbols[i] = dna->sequences[j][i];
			}

			if (count == most_common_symbol_count && dna->sequences[j][i] < smallest_character) {
				smallest_character = dna->sequences[j][i];
				most_common_symbols[i] = dna->sequences[j][i];
			}
		}
	}

	most_common_symbols[dna->sequence_symbol_count] = '\0';

	return most_common_symbols;
}

int ComputeHammingDistance(DNA_Matrix* dna) {
	char* most_common_symbols = SeekCommonElements(dna);
	int hamming_distance = 0;

	for (int i = 0; i < dna->sequence_symbol_count; ++i) {

		for (int j = 0; j < dna->amount_of_sequences; ++j) {

			if (dna->sequences[j][i] != most_common_symbols[i]) {
				++hamming_distance;
			}
		}
	}
	
	fprintf(stdout, "%s\n", most_common_symbols);
	free(most_common_symbols);

	return hamming_distance;
}

void ReadFromStream(FILE* f) {
	int test_count = 0;

	if ((fscanf(f, "%d", &test_count) != 1) || test_count < 0) {
		fprintf(stderr, "ERROR: INVALID ARGUMENT!!!\n");
		return;
	}

	for (int i = 0; i < test_count; ++i) {
		int amount = 0;
		int sequence_size = 0;


		if ((fscanf(f, "%d%d", &amount, &sequence_size) != 2) || amount < 0 || sequence_size < 0) {
			fprintf(stderr, "ERROR: INVALID ARGUMENT!!!\n");
			return;
		}

		DNA_Matrix* dna = Constructor(amount, sequence_size);

		for (int i = 0; i < amount; ++i) {
			if (fscanf(f, "%s", dna->sequences[i]) != 1) {
				fprintf(stderr, "ERROR: SOMETHING WENT WRONG!!!\n");
				return;
			}
		}

		fprintf(stdout, "%d\n", ComputeHammingDistance(dna));
		Destructor(dna);
	}
}