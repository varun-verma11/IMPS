#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int checkIfNumber(char *num) {
  char *temp = num;
  while(*temp) {
    if (!isdigit(*temp)) return 0;
    temp++;
  }
  return 1;
}

int checkAllRegistersAreValid(char **regs) {
  while (*reg) {
    if (!checkRegister(*reg) || !checkIfNumber(*reg+1)) {
      return 0;
    }
    reg++;
  }
  return 1;
}

void printInvalidCommandMessage(void) {
  printf("(JVG) invalid command. Please enter --help for help\n (JVG)");
}

void searchRegister(struct Processor *proc, char **tokens) {
  int start =0;
  int end = NUMBER_OF_REGISTERS;
  if (!checkIfNumber(tokens[1])) {
    printInvalidCommandMessage();
    return;
  }
  int value = atoi(tokens[1]);
  
  if (!checkAllRegistersAreValid(tokens+1)) {
    printInvalidCommandMessage();
    return;
  }
  
  if (strcmp(tokens[0],"-r")==0) {
    start = getRegisterNumber(token[2]);
    end = getRegisterNumber(tokens[3]);
    if (start<0 || start>end || end>=NUMBER_OF_REGISTERS) {
      printInvalidCommandMessage();
      return;
    }
    if (tokens[4]!=NULL) {
       printInvalidCommandMessage();
       return;
    }
  } else if (strcmp(tokens[0],"-a")!=0) {
    printInvalidCommandMessage();
    return;
  }
  
  printf("\n(JVG)");
  for (int i = start; i<end ; i++) {
    if (proc->gpr[i]==value) {
      printf("$%i=%i  ",i,getRegisterValue(getRegisterNumber));
    }
  }
  printf("\n(JVG)");
}

int checkIfAllValidNumbers(char **tokens) {
  while(*tokens) {
    if (!checkIfNumber(*tokens)) return 0;
    tokens++;
  }
  return 1;
}

void printMemory(struct Processor *proc, char **tokens) {
  int start = 0;
  int end = MEMORY_SIZE;
  if (checkIfAllValidNumbers(tokens+1)) {
    printInvalidCommandMessage();
    return;
  }
  if (strcmp(tokens[0],"-r")) {
    start = atoi(tokens[1]);
    end = atoi(tokens[2]);
    if (start<0 || start>end || end>=MEMORY_SIZE) {
      printInvalidCommandMessage();
      return;
    }
    if (tokens[4]!=NULL) {
       printInvalidCommandMessage();
       return;
    }
  } else if (strcmp(tokens[0],"-m")) {
    while (*tokens) {
    
    }
  }
}

void searchMemory(struct Processor *proc, char **tokens) {
  int start =0;
  int end = MEMORY_SIZE;
  if (!checkIfAllValidNumbers(tokens+1)) {
    printInvalidCommandMessage();
    return;
  }
  int value = atoi(tokens[1]);
  if (strcmp(tokens[0],"-r")==0) {
    start = getRegisterNumber(token[2]);
    end = getRegisterNumber(tokens[3]);
    if (start<0 || start>end || end>=MEMORY_SIZE) {
      printInvalidCommandMessage();
      return;
    }
    if (tokens[4]!=NULL) {
       printInvalidCommandMessage();
       return;
    }
  } else if (strcmp(tokens[0],"-a")!=0) {
    printInvalidCommandMessage();
    return;
  }  
  printf("\n(JVG)");
  for (int i = start; i<end ; i++) {
    if (proc->gpr[i]==value) {
      printf("M%i=%i  ",i,getRegisterValue(getRegisterNumber));
    }
  }
  printf("\n(JVG)");
}

void search(struct Processor *proc,char **tokens) {
  if (strcmp(token[0],"-M") ==0) {
    searchMemory(proc,tokens+1);
  } else if (strcmp(token[0],"-R")==0) {
    searchRegisters(proc,tokens+1);
  }
}

