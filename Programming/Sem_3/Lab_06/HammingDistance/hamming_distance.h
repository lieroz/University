#ifndef __HAMMING_DISTANCE_H_DEF__
#define __HAMMING_DISTANCE_H_DEF__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char** sequences;

	int amount_of_sequences;
	int sequence_symbol_count;
} DNA_Matrix;

void ReadFromStream(FILE*);

#endif // __HAMMING_DISTANCE_H_DEF__