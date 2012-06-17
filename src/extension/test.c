
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MIN(a, b) (a > b ? b : a)

#define MEMORY_SIZE 65536
#define NUMBER_OF_REGISTERS 32
#define NUMBER_OF_COMMANDS 8
#define BUFFER_SIZE 300   
char debugInstructions[][NUMBER_OF_COMMANDS] = {"list","stp","reg","mem","search","pc", "run", "q","--help"};

enum opCodes {HALT, ADD, ADDI, SUB,SUBI,MUL,MULI,LW,SW,BEQ, BNE, BLT, BGT, BLE, 
                BGE, JMP, JR, JAL, OUT, DIV, DIVI, MOD, MODI, FACT, FACTI,SWAP};

struct Processor {
  uint32_t pc;
  int32_t gpr[NUMBER_OF_REGISTERS];
  uint8_t memory[MEMORY_SIZE]; 
};
/*
  This method checks if the given tokenn is a register or not.
  @param token : specifes the token to be checked
  @return      : returns 1 if the given token is a register
*/
int checkRegister(char *token){
 return (token!=NULL) ? (token[0]=='$') : 0;
}

/*
  This method returns an integer value for the given register
  @param reg : specifes the reg whose int value has to be returned
  @return    : returns integer representation of the given string value 
               representation of the token
*/
int getRegisterNumber(char *reg){
  return atoi(reg+1);
}



int checkIfNumber(char *num) {
  char *temp = num;
  while(*temp) {
    if (!isdigit(*temp)) return 0;
    temp++;
  }
  return 1;
}


void printInvalidCommandMessage(void) {
  printf("(JVG) invalid command. Please enter --help for help\n (JVG)");
}


int checkAllRegistersAreValid(char **regs) {
  while (*regs) {
    if (!checkRegister(*regs) || !checkIfNumber(*regs+1) || 
              getRegisterNumber(*regs) <0 || 
              getRegisterNumber(*regs) >= NUMBER_OF_REGISTERS) {
      return 0;
    }
    regs++;
  }
  return 1;
}

/*
  This method returns the value stored in the specified register
  @param reg  : specifies the register index whose value has to be returned
  @param proc : specifies the processor from which the value of register has to
                be returned
  @return     : returns the value of the register specifed by the index given
*/
int32_t getRegisterValue(struct Processor *proc, int8_t reg){
  return proc->gpr[reg];
}

void printReg(struct Processor *proc , char **tokens) {
  int start = 0 ;
  int end = NUMBER_OF_REGISTERS-1;
  
  if (strcmp("-r",tokens[0])==0) {
    start = getRegisterNumber(tokens[1]);
    end   = getRegisterNumber(tokens[2]);
    tokens++;
    if(!start<end && !checkAllRegistersAreValid(tokens+1)){
      printInvalidCommandMessage();
      return;
    }
    if(tokens[2]!=NULL){
      printInvalidCommandMessage();
      return;
    }
  }
  else if (strcmp("-m",tokens[0])==0) {
    tokens++;
    if(!checkAllRegistersAreValid(tokens)){
      printInvalidCommandMessage();
      return;
    }
    int i =0;
    while(tokens[i]!=NULL) {
        printf("%s = %i \t",tokens[i],getRegisterValue(proc, getRegisterNumber(tokens[i])));
        i++;
      if (i%8==0) printf("      \n");
    }
    printf("\n (JVG)");
    return;    
  } 
  else if (!strcmp("-a",tokens[0])==0){
    printInvalidCommandMessage();
    return;
  } 
 int x=start;
 printf("%i,%i\n",x, end);
  for (int i=0; i<end%8 ; i++) {    
    for (int j=0;j<8 ; j++) {
      if(x>end) break;
      printf("$%i = %i \t",x,getRegisterValue(proc,x));
      x++;
    }
    printf("      \n");
  }  
}

int checkIfAllMemoryLocationsAreValid(char **tokens) {
  while(*tokens) {
    if (!checkIfNumber(*tokens) || atoi(*tokens) <0 
                || atoi(*tokens)>=MEMORY_SIZE) {
      return 0;
      }   
    tokens++;
  }
  return 1;
}
/*
  This method returns the data stored at in the memory of the specifed processor
  at the specified address.
  @param proc    : specifies the processor 
  @param address : specifies the address of the memory which data has to be
                   fetched
  @return        : returns the value stored in the memory at the specified
                   address
*/
uint32_t getMemory(struct Processor *proc, uint32_t address) {
  return *(uint32_t *)(proc->memory + address);
}

void printMemory(struct Processor *proc, char **tokens) {
  int start = 0;
  int end = MEMORY_SIZE-1;

  if ((strcmp(tokens[0],"-r"))==0) {
    start = atoi(tokens[1]);
    end = atoi(tokens[2]);
    tokens++;
    if (start>end) {
      printInvalidCommandMessage();
      return;
    }
    if (tokens[4]!=NULL) {
       printInvalidCommandMessage();
       return;
    }
  } else if ((strcmp(tokens[0],"-m"))==0) {
    int j=0;
    tokens++;
      if (!checkIfAllMemoryLocationsAreValid(tokens+1)) {
        printInvalidCommandMessage();
        return;
      }
    while (*tokens) {
      printf("M%i=%i  ",atoi(*tokens),getMemory(proc,atoi(*tokens)));
      tokens++;
      j++;
      if (j%8==0) printf("\n");
    }
    printf("\n (JVG)");
    return; 
  } else if ((strcmp(tokens[0],"-a"))!=0) {
    printInvalidCommandMessage();
    return;
  }
  int x= start;
  for (int c=0; x<end ; c++) {
    for (int d=0;d<8&&x<=end ;d++) {
      printf("M%i=%i \t",x,getMemory(proc,x));
      x++;
    }
    printf("\n");
  }
  
}

void searchMemory(struct Processor *proc, char **tokens) {
  int start =0;
  int end = MEMORY_SIZE-1;
  printf("%s \n",tokens[0]);
  printf("tokens1%s, tokens 2 %s\n",tokens[0],tokens[1]);
  if (!checkIfAllMemoryLocationsAreValid(tokens+1)) {
    printInvalidCommandMessage();
    return;
  }
  int value = atoi(tokens[1]);
  if (strcmp(tokens[0],"-r")==0) {
    start = atoi(tokens[2]);
    end = atoi(tokens[3]);
    if (start>end) {
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
      printf("M%i=%i  ",i,value);
    }
  }
  printf("\n(JVG)");
}

void search(struct Processor *proc,char **tokens) {
  if (strcmp(tokens[0],"-M") ==0) {
    searchMemory(proc,tokens+1);
  } else if (strcmp(tokens[0],"-R")==0) {
    //searchRegisters(proc,tokens+1);
  }
}

int executeUserCommand(/*char *assembly, char *bin, */struct Processor *proc, char **tokens) {
  if (strcmp(tokens[0], "reg")==0) {
    tokens++;
    printReg(proc, tokens);
    return 0;
  } else if (strcmp(tokens[0], "mem")==0) {
    tokens++;
    printMemory(proc, tokens);
    return 0;
  } else if (strcmp(tokens[0], "pc\n")==0) {
    //printPC(proc);
    return 0;
  } else if (strcmp(tokens[0], "search")==0) {
    tokens++;
    search(proc, tokens);
    return 0;
  } else if (strcmp(tokens[0], "stp\n")==0) {
    //step(proc);
    return 0;
  } else if (strcmp(tokens[0], "list\n")==0) {
    //listInstruction(assembly, ((proc->pc)/4)+1);
    return 0;
  } else if (strcmp(tokens[0], "--help\n")==0) {
    //system("cat help.txt | less");
    return 0;
  } else if (strcmp(tokens[0], "run\n")==0) {
    //run(proc);
    //char cmd[] = "./emulate ";
    // *cmd = *strcat(cmd,bin);
    //system(cmd);
    return 0;
  } else if (strcmp(tokens[0],"q")) {
    //return confirmToQuit();
  }
  return 1;
}
char **tokeniseUserCommand(char *command) {
  char *buff = malloc(sizeof(char) * BUFFER_SIZE);
  buff = strncpy(buff,command,sizeof(char) *BUFFER_SIZE);
  char **tokens = malloc(sizeof(char) *BUFFER_SIZE);
  char *token = malloc(50);
  int i=0;
  token = strtok(buff," ");
  tokens[i] = token;
  while(token!=0) {
    i++;
    token = strtok(NULL," ");
    tokens[i] = token;
  }  
  return tokens;
}





int main(void) {
  char *fp = "simple.bin";
  struct Processor *proc = malloc(sizeof(struct Processor));
  memset(proc,0,sizeof(struct Processor));
  char **tokens = malloc(300);
  //char *cmd = malloc(100);
  char* cmd = "search -M -r 10 20";
  tokens = tokeniseUserCommand(cmd);
  executeUserCommand(proc, tokens);
  return 1;
}


