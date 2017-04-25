#include "stream.h"
#include <stdio.h>

STREAM_T OpenFile(char* name) {
	return fopen(name, "r");
}

void Close_Stream(Stream* S) {
	fclose(S->F);
}

STREAM_T open_stream(Stream* S, char* name) {
	return S->F = OpenFile(name);
}


int stream_EOF(Stream S) {
	return feof(S.F);
}

char scan_char(Stream* S) {
	char ch;
	
	if (fscanf(S->F, "%c", &ch)) {
		return ch;
	}
	
	return 0;
}

void stream_rewind(Stream* S) {
	rewind(S->F);
}

FILE* get_stream(Stream S) {
	return S.F;
}
