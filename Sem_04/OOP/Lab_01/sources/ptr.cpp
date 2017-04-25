#include "ptr.h"
#include <stdlib.h>

void Clear_Ptr(void* ptr) {
	free(ptr);
}

void* Get_mem(int size_type, size_t count) {
	return malloc(count * size_type);
}
