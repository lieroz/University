#ifndef __STATE_MACHINE_H_DEF__
#define __STATE_MACHINE_H_DEF__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "cstack.h"

#define NUMBER_OF_KEYWORDS 38
#define NUMBER_OF_OPERATORS 30

typedef enum {
	ST_USUAL,
	ST_MULTILINE_COMMENT,
	ST_STRING_LITERAL,
	ST_PUNCTUATOR,
	ST_CONSTANT,
	ST_IDENTIFIER,
} state_t;

//--------------------------------------------------------------

void ReadFromStream(FILE*, FILE*);

#endif // __STATE_MACHINE_H_DEF__