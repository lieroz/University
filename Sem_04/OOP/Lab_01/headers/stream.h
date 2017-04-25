#ifndef STREAM
#define STREAM

#include <stdio.h>

#define STREAM_T FILE*

typedef struct STREAM_TYPE {
	STREAM_T F;
} Stream;

STREAM_T open_stream(Stream* S, char* name);
void Close_Stream(Stream* S);
int stream_EOF(Stream S);
STREAM_T OpenFile(char* name);
void stream_rewind(Stream* S);
STREAM_T get_stream(Stream S);

#endif // STREAM

