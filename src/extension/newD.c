#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MIN(a, b) (a > b ? b : a)

#define MEMORY_SIZE 65536
#define NUMBER_OF_REGISTERS 32
#define NUMBER_OF_COMMANDS 9
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

void printLine(char *filepath, int n){
  FILE *fp;
  fp = fopen(filepath,"r");
  char *buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
  if (fp==NULL) {
    perror("ERROR in opening file");
    exit(EXIT_FAILURE);
  }
  int i=1;
  while (!feof(fp) &&i<n ){
    i++; 
    memset(buffer, 0, ((sizeof(char))*BUFFER_SIZE));
    fgets (buffer, BUFFER_SIZE, fp); 
  
  }
  if(i==n) {
    printf("%s", buffer);
  }
  else{
    perror("End of file reached before line");
  }                  
  free(buffer);
  fclose(fp);

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
    if(!start<end && !checkAllRegistersAreValid(tokens+1)){
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
  
  } 
  else if (!strcmp("-a",tokens[0])==0){
    printInvalidCommandMessage();
    return;
  } 
  printf( "\nstart- > %i   end -> %i\n",start, end);
  for (int i=start; i<end/8 ; i++) {     
    for (int j=0;j<8 ; j++) {
      printf("%s = %i \t",tokens[(i*j) + j],getRegisterValue(proc,getRegisterNumber(tokens[(i*j) + j])));
    }
    printf("      \n");
  }  
}

void searchRegisters(struct Processor *proc, char **tokens) {
  int start =0;
  int end = NUMBER_OF_REGISTERS-1;
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
    start = getRegisterNumber(tokens[2]);
    end = getRegisterNumber(tokens[3]);
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
      printf("$%i=%i  ",i,value);
    }
  }
  printf("\n(JVG)");
}

int checkIfAllMemoryLocationsAreValid(char **tokens) {
  while(*tokens) {
    if (!checkIfNumber(*tokens) || atoi(*tokens) <0 
                || atoi(*tokens)>=MEMORY_SIZE) return 0;
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
  if (checkIfAllMemoryLocationsAreValid(tokens+1)) {
    printInvalidCommandMessage();
    return;
  }
  if (strcmp(tokens[0],"-r")) {
    start = atoi(tokens[1]);
    end = atoi(tokens[2]);
    if (start>end) {
      printInvalidCommandMessage();
      return;
    }
    if (tokens[4]!=NULL) {
       printInvalidCommandMessage();
       return;
    }
  } else if (strcmp(tokens[0],"-m")) {
    int j=0;
    while (*tokens) {
      printf("M%i=%i  ",atoi(*tokens),getMemory(proc,atoi(*tokens)));
      tokens++;
      j++;
      if (j%8==0) printf("\n");
    }
  } else if (strcmp(tokens[0],"-a")!=0) {
    printInvalidCommandMessage();
    return;
  }
  
  for (int c=start; c<start/8 ; c++) {
    for (int d=0;d<8 ;d++) {
      printf("M%i=%i  ",(c*d) +d,getMemory(proc,atoi(*tokens)));
    }
    printf("\n");
  }
  
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

void searchMemory(struct Processor *proc, char **tokens) {
  int start =0;
  int end = MEMORY_SIZE-1;
  if (!checkIfAllMemoryLocationsAreValid(tokens+1)) {
    printInvalidCommandMessage();
    return;
  }
  int value = atoi(tokens[1]);
  if (strcmp(tokens[0],"-r")==0) {
    start = getRegisterNumber(tokens[2]);
    end = getRegisterNumber(tokens[3]);
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
    searchRegisters(proc,tokens+1);
  }
}



void printPC( struct Processor *proc) {
  printf("PC = %x \n",proc->pc);
}



/*
  This method returns the opcode (bit 0 to 5) from the given 32 bit instruction
  @param instruction : This specifies the 32 bit instruction
  @return            : The method returns 8bit representation of the opcode
*/
uint8_t getOpcode(uint32_t instruction) {
  uint32_t mask = 0xfc000000;
  uint32_t opcd = mask & instruction;
  opcd = opcd >> 26;
  uint8_t opCode = (int) opcd;
  return opCode;
}
/*
  This method returns the bit 6 to 31 of the given instruction, i.e. the address
  for j-type instructions
  @param instruction : this specifies the instruction
  @return            : the method returns 32 bit representation of the bit 6 to 
                       31 of the given instruction
*/
uint32_t getAddress(uint32_t instruction) {
  uint32_t mask = 0x03ffffff;
  return mask & instruction;
}
/*
  This method returns the bit 6 to 10 of the given instruction
  @param instruction : this specifies the instruction
  @return            : the method returns 8 bit representation of the bit 6 to 
                       10 of the given instruction
*/
uint8_t getR1(uint32_t instruction){
  uint32_t mask = 0x03e00000;
  uint32_t reg = mask & instruction;
  uint8_t r1 = reg>>21;
  return r1;

}
/*
  This method returns the bit 11 to 15 of the given instruction
  @param instruction : this specifies the instruction
  @return            : the method returns 8 bit representation of the bit 11 to 
                       15 of the given instruction
*/
uint8_t getR2(uint32_t instruction) {
  uint32_t mask = 0xf8000;
  uint32_t reg = mask & instruction;
  uint8_t r2 = reg >> 16;
  return r2;
}


/*
  This method returns the bit 16 to 21 of the given instruction
  @param instruction : this specifies the instruction
  @return            : the method returns 8 bit representation of the bit 16 to 
                       21 of the given instruction
*/
uint8_t getR3(uint32_t instruction) {
  uint32_t mask = 0x0007C00;
  return ((mask & instruction) >> 11);
}/*
  This method returns the bit 16 to 31 of the given instruction
  @param instruction : this specifies the instruction
  @return            : the method returns 8 bit representation of the bit 16 to 
                       31 of the given instruction
*/
int16_t getImmediateValue(uint32_t instruction) {
  uint32_t mask = 0x0000ffff;
  return (int16_t)(mask & instruction);
}


/*
  This method sets the value of the memory at the specified addredd to the value
  given.
  @param proc    : specifies the processor
  @param address : specifies the address of memory which needs the value to be
                   set to the given value
  @param value   : specifies the new value for the memory to be set
*/
void setMemory(struct Processor *proc, uint32_t address, int32_t value) {
  *(uint32_t *)(proc->memory + address) = value;
}


/*
  This method returns the instruction stored in the memory at address specified
  by the program counter of the processor.
  @param proc : specifies the processor which contains the program counter,
                memory, and registers
*/
uint32_t getInstructionAtPC(struct Processor *proc){
  return *(uint32_t *)(proc->memory + proc->pc);
}



int carryOutInstruction(struct Processor *processor) {
  uint32_t instruction = getInstructionAtPC(processor);
  uint8_t opcode = getOpcode(instruction);
  uint32_t backupPC = processor->pc;
  int32_t temp;
  div_t division;

  switch (opcode)  {
    case HALT : return 0;
    case ADD  : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) + 
                  getRegisterValue(processor, getR3(instruction));
                break;
                
    case ADDI : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) + 
                  getImmediateValue(instruction);
                break;
               
    case SUB  : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) - 
                  getRegisterValue(processor, getR3(instruction));
                break;
                
    case SUBI : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) - 
                   getImmediateValue(instruction);
                 break;
                  
    case MUL  : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) * 
                  getRegisterValue(processor, getR3(instruction));
                break;
                  
    case MULI : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) * 
                  getImmediateValue(instruction);
                break;
                
    case LW   : processor->gpr[getR1(instruction)] = 
                getMemory(processor, 
                          getRegisterValue(processor, getR2(instruction)) + 
                                            getImmediateValue(instruction));
                break;
                  
    case SW   : setMemory(processor, getRegisterValue
                  (processor, getR2(instruction)) + 
                  getImmediateValue(instruction), 
                  getRegisterValue(processor, getR1(instruction)));
                break;
                
    case BEQ  : if (processor->gpr[getR1(instruction)] == 
                    processor->gpr[getR2(instruction)]) 
                  { processor->pc += getImmediateValue(instruction) * 4;};
                break;
                  
      case BNE  : if (processor->gpr[getR1(instruction)] != 
                      processor->gpr[getR2(instruction)]) 
                    { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BLT  : if (processor->gpr[getR1(instruction)] <
                      processor->gpr[getR2(instruction)])
                    { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BGT  : if (processor->gpr[getR1(instruction)] >
                     processor->gpr[getR2(instruction)]) 
                   { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BLE  : if (processor->gpr[getR1(instruction)] <= 
                      processor->gpr[getR2(instruction)]) 
                  { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BGE  : if (processor->gpr[getR1(instruction)] >= 
                      processor->gpr[getR2(instruction)]) 
                    { processor->pc += (getImmediateValue(instruction) * 4);};
                  break;
                  
      case JMP  : processor->pc = getAddress(instruction);
                  break;
                  
      case JR   : processor->pc = getRegisterValue
                    (processor, getR1(instruction));
                  break;
                  
      case JAL  : processor->gpr[31] = processor->pc + sizeof(uint32_t); 
                  processor->pc = getAddress(instruction);
                  break;
                  
      case OUT  : printf("%c", (char)getRegisterValue
                    (processor, getR1(instruction)));
                  break;
                  
      case DIV  : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getRegisterValue(processor,getR3(instruction)));
                  processor->gpr[getR1(instruction)] = division.quot;
      
      case DIVI : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getImmediateValue(instruction));
                  processor->gpr[getR1(instruction)] = division.quot;
      
      case MOD  : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getRegisterValue(processor,getR3(instruction)));
                  processor->gpr[getR1(instruction)] = division.rem;
      
      case MODI : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getImmediateValue(instruction));
                  processor->gpr[getR1(instruction)] = division.rem;
      
      case FACT : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction));
                  for(int i = 1; i<processor->gpr[getR2(instruction)] ; i++) {
                    processor->gpr[getR1(instruction)] = 
                      (getRegisterValue(processor, getR1(instruction)))*
                      (getRegisterValue(processor, getR2(instruction))-i);};
                  break;
      
      case FACTI: processor->gpr[getR1(instruction)] = 
                  getImmediateValue(instruction);
                  for(int i = 1; i<getImmediateValue(instruction) ; i++) {
                    processor->gpr[getR1(instruction)] = 
                      (getRegisterValue(processor, getR1(instruction)))*
                      (getImmediateValue(instruction)-i);};
                  break;
      
      case SWAP : temp = 
                    getRegisterValue(processor, getR1(instruction));
                  processor->gpr[getR1(instruction)] = 
                    getRegisterValue(processor, getR2(instruction));
                  processor->gpr[getR2(instruction)] = temp;
                  break;
                  
      default   : printf("invalid opcode\n");
                  break;
    }
    
    if(processor->pc == backupPC)  processor->pc += sizeof(uint32_t);
    return 1;
}


void step(struct Processor *proc) {
  carryOutInstruction(proc);
  printf("(JVG) ");
}



/*
  The method binaryFileLoader loads the binary file in the memory of the given
  processor.
  @param processor : this specifes the current processor with the memory to be
                     initialised with the given instructions from given filepath
  @param filepath  : this specifies the path of the file which contains the
                     instructions to be loaded in the memory.
*/
void binaryFileLoader(char *filepath, struct Processor *processor) {
  FILE *fp;
  fp = fopen(filepath,"rb");
  if (fp==NULL) {
    perror("ERROR in opening file");
    exit(EXIT_FAILURE);
  }

  int fileSize;
  
  fseek (fp , 0 , SEEK_END);
  fileSize = ftell (fp);
  rewind (fp);

  fileSize = MIN(65536, fileSize);

  fread(processor->memory, sizeof(uint32_t), fileSize, fp);
  fclose(fp);
}

void listInstruction(char *instruction) {
  printf("(JVG) %s \n (JVG)",instruction);
}



/*
  This method prints the state of the processor at the end of execution of the
  program; i.e. the data stored in all the registers and the value of program
  counter at the end of the program
  @param proc : this specifies the processor whose state has to be printed
*/
void dumpProcessor(struct Processor *proc) {
  fprintf(stderr, "\n\n-----\n\nPC=%d\n", proc->pc);
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++) {
       int reg = i * 8 + j;
       fprintf(stderr, "R%d=%d\t", reg, getRegisterValue(proc, reg));
    }
      fprintf(stderr, "\n");
   }
}



void printWelcomeMessage(void){
  printf("Welcome to JVG debugger for binary programs for IMPS instruction set. \n Please type the specific commands for the task or enter --help  for help. \n\n");
}

int checkUserCommandIsValid(char *command) {
  for (int i=0; i<NUMBER_OF_COMMANDS; i++) {
    if (strncmp(command,debugInstructions[i],sizeof(char)*strlen(debugInstructions[i]))==0) return 1;
  }
  return 0;
}

char **getUserCommand(void) {
  printf("(JVG)");
  char *buff = malloc(BUFFER_SIZE);
  fgets(buff,BUFFER_SIZE,stdin);
  char **tokens = malloc(sizeof(char) * BUFFER_SIZE);
  tokens = tokeniseUserCommand(buff);
  if (checkUserCommandIsValid(tokens[0])) return tokens;
  printf("(JVG) INVALID COMMAND: Please enter a valid command or type '--help' for help \n");
  return getUserCommand();
}

int confirmToQuit() {
  printf("(JVG) are you sure you want to quit? enter y for yes and n for no\n(JVG)");
  char *ans = malloc(sizeof(char) * BUFFER_SIZE);
  fgets(ans,sizeof(char) * 2, stdin);
  int ret = strcmp(ans,"y")==0; 
  if (ret==0 && strcmp(ans,"n")!=0) {
    free(ans);
    printf("Please enter a valid answer\n");
    return confirmToQuit();
  } 
  free(ans);
  return ret;
}
 
int executeUserCommand(char *assembly, char *bin, struct Processor *proc, char **tokens) {
  if (strcmp(tokens[0], "reg")==0) {
    tokens++;
    printReg(proc, tokens);
    return 0;
  } else if (strcmp(tokens[0], "mem")==0) {
    tokens++;
    printMemory(proc, tokens);
    return 0;
  } else if (strcmp(tokens[0], "pc\n")==0) {
    printPC(proc);
    return 0;
  } else if (strcmp(tokens[0], "search")==0) {
    tokens++;
    search(proc, tokens);
    return 0;
  } else if (strcmp(tokens[0], "stp\n")==0) {
    step(proc);
    return 0;
  } else if (strcmp(tokens[0], "list\n")==0) {
    printLine(assembly, ((proc->pc)/4)+1);
    return 0;
  } else if (strcmp(tokens[0], "--help\n")==0) {
    system("cat help.txt | less");
    return 0;
  } else if (strcmp(tokens[0], "run\n")==0) {
    char cmd[] = "./emulate ";
    *cmd = *strcat(cmd,bin);
    system(cmd);
    return 0;
  } else if (strcmp(tokens[0],"q")) {
    return confirmToQuit();
  }
  return 1;
}

int main(int argc, char **argv) {
  struct Processor *proc = malloc(sizeof(struct Processor));
  assert("There are wrong number of arguents given" && argc==3);
  char *fBin = argv[2];
  char *fAssembly = argv[1];
  memset(proc,0,sizeof(struct Processor));
  binaryFileLoader(fBin,proc);
  printWelcomeMessage();
  char **tokens = malloc(sizeof(char) *BUFFER_SIZE);
  int returnVal = 0; 
  do {
    tokens = getUserCommand();
    returnVal = executeUserCommand(fAssembly,fBin,proc,tokens);
  } while (!returnVal);
  
  return EXIT_SUCCESS;
}
