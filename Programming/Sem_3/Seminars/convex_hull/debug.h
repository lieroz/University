#ifndef DEBUG_H
	#define DEBUG_H
	#include <stdio.h>
	#define PDEBUG(fmt, ...)
	#define ZDEBUG
	#ifdef DEBUG
		#undef PDEBUG
		#define PDEBUG(fmt, ...) fprintf(stdout, "%s: %d: \n" fmt, __FUNCTION__, __LINE__, __VA_ARGS__);
		#undef ZDEBUG
		#define ZDEBUG fprintf(stdout, "%s: %d: \nStack: ", __FUNCTION__, __LINE__);

	#endif // DEBUG
#endif // DEBUG_H