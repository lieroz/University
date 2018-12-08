CC=gcc
CFLAGS=
DEPS=
OBJ=main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lab_04: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o lab_04
