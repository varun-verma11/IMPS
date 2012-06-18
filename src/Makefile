CC      = gcc
CFLAGS  = -Wall -pedantic -std=c99

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate debugger

parser.o: parser.c parser.h table.h

checkOptype.o : checkOptype.c checkOptype.h

tokeniser.o: tokeniser.c tokeniser.h

table.o : table.c table.h

assemble.o: assemble.c assemble.h parser.h checkOptype.h tokeniser.h table.h

emulate.o : emulate.c

debugger.o: debugger.c

assemble: assemble.o parser.o checkOptype.o tokeniser.o table.o
	$(CC)  $(CFLAGS) -o $@ $^

debugger: debugger.o
	$(CC) $(CFLAGS) -o $@ $^

emulate: emulate.o
	$(CC) $(CFLAGS) -o $@ $^
	
clean:
	rm -f *.o
	rm -f assemble
	rm -f emulate
	rm -f debugger
