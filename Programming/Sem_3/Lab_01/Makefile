CC = gcc
CFLAGS = -c -Wall -Werror -Wextra
LDFLAGS = 
SOURCES = main.c prettytable.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = out

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@