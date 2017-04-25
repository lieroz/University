#ifndef PROCESSOR
#define PROCESSOR

#include "action.h"

enum action {
	LOAD,
	CHANGE,
	DRAW,
	CLEAR
};

errs_num processor(argument* arg, action act);

#endif // PROCESSOR

