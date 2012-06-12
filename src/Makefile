CC      = gcc
CFLAGS  = -Wall

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble.o: assemble.c a.h 

b.o: b.c a.h

assemble: assemble.o a.o
	$(CC) $(CFLAGS) -o $@ $^

emulate: emulate.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f assemble
	rm -f emulate
