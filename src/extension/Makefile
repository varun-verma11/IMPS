CC      = gcc
CFLAGS  = -Wall -pedantic -std=c99

.SUFFIXES: .c .o

.PHONY: all clean

all: emulate

emulate_getting_registers.o: emulate_getting_registers.c emulate.h

emulate.o : emulate.c emulate_getting_registers.c emulate.h

emulate: emulate.o emulate_getting_registers.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f assemble
	rm -f emulate
