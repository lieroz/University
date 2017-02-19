#ifndef DEBUG_H
	#define DEBUG_H
	#include <stdio.h>
	#define PDEBUG(fmt, ...)

	#ifdef DEBUG
		#undef PDEBUG
		#define PDEBUG(fmt, ...) fprintf(stdout, "%s: %d: \n" fmt, __FUNCTION__, __LINE__, __VA_ARGS__);

	#endif // DEBUG
#endif // DEBUG_H