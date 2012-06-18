CC      = gcc
CFLAGS  = -Wall -pedantic -std=c99

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate extension

parser.o: parser.c parser.h table.h

checkOptype.o : checkOptype.c checkOptype.h

tokeniser.o: tokeniser.c tokeniser.h

table.o : table.c table.h

assemble.o: assemble.c assemble.h parser.h checkOptype.h tokeniser.h table.h

emulate.o : emulate.c

carryOutInstruction.o: carryOutInstruction.c carryOutInstruction.h

emulate.o : emulate.c carryOutInstruction.h emulate.h

debugger.o : debugger.c carryOutInstruction.h userCommands.h debugger.h

userCommands.o : userCommands.c userCommands.h carryOutInstruction.h parser.h emulate.h

extension : debugger.o carryOutInstruction.o userCommands.o
	$(CC) $(CFLAGS) -o $@ $^

emulate: emulate.o carryOutInstruction.o
	$(CC) $(CFLAGS) -o $@ $^

assemble: assemble.o parser.o checkOptype.o tokeniser.o table.o
	$(CC)  $(CFLAGS) -o $@ $^
	
clean:
	rm -f *.o
	rm -f assemble
	rm -f emulate
	rm -f extension
