#include "debugger.h"

void executeUserCommand(char *fp, struct Processor *proc, char **tokens) {
  if (strcmp(tokens[0], "reg")==0) {
    tokens++;
    printReg(proc, tokens);
  }
  else if (strcmp(tokens[0], "mem")==0) {
    tokens++;
    printMemory(proc, tokens);
  }
  else if (strcmp(tokens[0], "pc")==0) {
    printPC(proc);
  }
  else if (strcmp(tokens[0], "search")==0) {
    tokens++;
    search(proc, tokens);
  }
  else if (strcmp(tokens[0], "stp")==0) {
    step(proc);
  }
  else if (strcmp(tokens[0], "list")==0) {
    printLine(fp, ((proc->pc)/4)+1);
  }
  else if (strcmp(tokens[0], "--help")==0) {
    system("cat help.txt | less");
  }
}

