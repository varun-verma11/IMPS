CC      = gcc
CFLAGS  = -Wall -pedantic -std=c99

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

parser.o: parser.c parser.h table.h

checkOptype.o : checkOptype.c checkOptype.h

tokeniser.o: tokeniser.c tokeniser.h

table.o : table.c table.h

assemble.o: assemble.c assemble.h parser.h checkOptype.h tokeniser.h table.h

emulate.o : emulate.c

debuggerChecks.o : debuggerChecks.c debuggerChecks.h

searchAndPrintRegMem.o : searchAndPrintRegMem.c searchAndPrintRegMem.h

carryOutInstructionForExtension.o : carryOutInstructionForExtension.c carryOutInstructionForExtension.h

debugger.o : debugger.c debugger.h carryOutInstructionForExtension.h searchAndPrintRegMem.h debuggerChecks.h

assemble: assemble.o parser.o checkOptype.o tokeniser.o table.o
	$(CC)  $(CFLAGS) -o $@ $^

emulate: emulate.o carryOutInstructionForExtension.o debuggerChecks.o searchAndPrintRegMem.o 
	$(CC) $(CFLAGS) -o $@ $^

debugger: debugger.o carryOutInstructionForExtension.o debuggerChecks.o searchAndPrintRegMem.o 
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f assemble
	rm -f emulate
	rm -f debugger
