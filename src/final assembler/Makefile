CC      = gcc
CFLAGS  = -Wall -pedantic -std=c99

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

parser.o: parser.c assemble.h

checkOptype.o : checkOptype.c assemble.h

tokeniser.o: tokeniser.c assemble.h

table.o : table.c assemble.h

assemble.o: assemble.c assemble.h parser.c checkOptype.c tokeniser.c table.c

emulate.o : emulate.c

assemble: assemble.o parser.o checkOptype.o tokeniser.o table.o
	$(CC)  $(CFLAGS) -o $@ $^

emulate: emulate.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f assemble
	rm -f emulate
