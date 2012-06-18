#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MIN(a, b) (a > b ? b : a)

#define MEMORY_SIZE 65536
#define NUMBER_OF_REGISTERS 32
#define NUMBER_OF_COMMANDS 11
#define NUMBER_OF_INSTRUCTIONS 26
#define BUFFER_SIZE 300      
#define BREAKPOINTS_ARRAY_SIZE 100
                
char debugInstructions[][NUMBER_OF_COMMANDS] = {"list","stp","reg","mem","search","pc", "run", "q","--help","break","back","rerun"};

enum opCodes {HALT, ADD, ADDI, SUB,SUBI,MUL,MULI,LW,SW,BEQ, BNE, BLT, BGT, BLE, 
                BGE, JMP, JR, JAL, OUT, DIV, DIVI, MOD, MODI, FACT, FACTI,SWAP};

struct Processor {
  uint32_t pc;
  int32_t gpr[NUMBER_OF_REGISTERS];
  uint8_t memory[MEMORY_SIZE]; 
};

//this is a global constant to store the state of the program, i.e. value 1 if program ran.
int programExitValue;

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
  printf("Invalid command. Please enter --help for help\n");
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
    if(start>end && !checkAllRegistersAreValid(tokens+1)){
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
        printf("%s = %i, \t",tokens[i],getRegisterValue(proc, getRegisterNumber(tokens[i])));
        i++;
      if (i%8==0) printf("\n");
    }
    printf("\n");
    return;    
  } 
  else if (!strcmp("-a",tokens[0])==0){
    printInvalidCommandMessage();
    return;
  } 

  for(int i = 0; i <=end/8; i++) {
    for(int j = 0; j < 8; j++) {
       int reg = i * 8 + j;
       fprintf(stderr, "R%d=%d\t", reg, getRegisterValue(proc, reg));
    }
      fprintf(stderr, "\n");
   }
  printf("\n");
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
    printf("\n");
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
    printf("mem search\n");
    searchMemory(proc,tokens+1);
  } else if (strcmp(tokens[0],"-R")==0) {
    searchRegisters(proc,tokens+1);
  }
}

int checkIfBreakPoint(int *breakPoints, int lineNumber) {
  for (int i=0; i<BREAKPOINTS_ARRAY_SIZE ;i++) {
    if (breakPoints[i]==lineNumber) return 1;
    if (breakPoints[i]==-1) return 0;
    i++;
  }
  return 0;
}

void printPC( struct Processor *proc) {
  printf("PC = %i \n",proc->pc);
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

void printSegmentationFaultMessage(void) {
  printf("Executing the current line would cause segmentation fault.\n");
  printf("Please use the 'list' command to track the line where the error occurred\n");
}

int checkRtypeInstructionIsValid(uint32_t ins) {
  uint8_t r1 = getR1(ins);
  uint8_t r2 = getR2(ins);
  uint8_t r3 = getR3(ins);
  if (r1<0 || r2<0 || r3<0 || r1>=NUMBER_OF_REGISTERS || r2>=NUMBER_OF_REGISTERS 
        || r3>=NUMBER_OF_REGISTERS) {
    printSegmentationFaultMessage();
    return 0;
  }
  return 1;
}

int checkBrachInstructionIsValid(uint32_t ins, struct Processor *proc) {
  uint8_t r1 = getR1(ins);
  uint8_t r2 = getR2(ins);
  int16_t iVal = getImmediateValue(ins);
  uint32_t pc = proc->pc;
  if (r1<0 || r2<0 || r1>=NUMBER_OF_REGISTERS || r2>=NUMBER_OF_REGISTERS 
                                || pc+(iVal*4)<0 || pc+(iVal*4)>=MEMORY_SIZE) {
    printSegmentationFaultMessage();
    return 0;
  }
  return 1;
}

int checkItypeInstructionIsValid(uint32_t ins) {
  uint8_t r1 = getR1(ins);
  uint8_t r2 = getR2(ins);
  if (r1<0 || r2<0 || r1>=NUMBER_OF_REGISTERS || r2>=NUMBER_OF_REGISTERS) {
    printSegmentationFaultMessage();
    return 0;
  }
  return 1;
}

int checkJtypeIsValid(uint32_t ins) {
  uint32_t add = getAddress(ins);
  if (add<0 || add>=MEMORY_SIZE) {
    printSegmentationFaultMessage();
    return 0;
  }
  return 1;
}

int checkIfLoadAndStoreAreValid(uint32_t ins) {
  uint8_t r1 = getR1(ins);
  uint8_t r2 = getR2(ins);
  int16_t iVal = getImmediateValue(ins);
  if (r1<0 || r2<0 || r1>=NUMBER_OF_REGISTERS || r2>=NUMBER_OF_REGISTERS 
                                        || r2+iVal<0 || r2+iVal>=MEMORY_SIZE) {
    printSegmentationFaultMessage();
    return 0;
  }
  return 1;
}

int carryOutInstruction(struct Processor *processor) {
  uint32_t instruction = getInstructionAtPC(processor);
  uint8_t opcode = getOpcode(instruction);
  if (opcode<0 || opcode>NUMBER_OF_INSTRUCTIONS) {
    printf("The opcode for the current instruction is invalid. This would cause SEGMENTATION FAULT\n");
    programExitValue =1;
    return 0;    
  };
  uint32_t backupPC = processor->pc;
  int32_t temp;
  div_t division;
  switch (opcode)  {
    case HALT : return 0;
    case ADD  : if (checkRtypeInstructionIsValid(instruction)==0) return 0;
                processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) + 
                  getRegisterValue(processor, getR3(instruction));
                break;
                
    case ADDI : if (checkItypeInstructionIsValid(instruction)==0) return 0;
                processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) + 
                  getImmediateValue(instruction);
                break;
               
    case SUB  : if (checkRtypeInstructionIsValid(instruction)==0) return 0;
                processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) - 
                  getRegisterValue(processor, getR3(instruction));
                break;
                
    case SUBI : if (checkItypeInstructionIsValid(instruction)==0) return 0;
                processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) - 
                   getImmediateValue(instruction);
                 break;
                  
    case MUL  : if (checkRtypeInstructionIsValid(instruction)==0) return 0;
                processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) * 
                  getRegisterValue(processor, getR3(instruction));
                break;
                  
    case MULI : if (checkItypeInstructionIsValid(instruction)==0) return 0;
                processor->gpr[getR1(instruction)] = 
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
                
    case BEQ  : if (checkBrachInstructionIsValid(instruction,processor)==0) 
                  return 0;
                if (processor->gpr[getR1(instruction)] == 
                    processor->gpr[getR2(instruction)]) 
                  { processor->pc += getImmediateValue(instruction) * 4;};
                break;
                  
    case BNE  : if (checkBrachInstructionIsValid(instruction,processor)==0) 
                return 0;
                if (processor->gpr[getR1(instruction)] != 
                    processor->gpr[getR2(instruction)]) 
                { processor->pc += getImmediateValue(instruction) * 4;};
                break;
                  
    case BLT  : if (checkBrachInstructionIsValid(instruction,processor)==0) 
                return 0;
                if (processor->gpr[getR1(instruction)] <
                   processor->gpr[getR2(instruction)])
                { processor->pc += getImmediateValue(instruction) * 4;};
                break;
                  
    case BGT  : if (checkBrachInstructionIsValid(instruction,processor)==0) 
                return 0;
                if (processor->gpr[getR1(instruction)] >
                  processor->gpr[getR2(instruction)]) 
                { processor->pc += getImmediateValue(instruction) * 4;};
                break;
                  
    case BLE  : if (checkBrachInstructionIsValid(instruction,processor)==0) 
                  return 0;
                if (processor->gpr[getR1(instruction)] <= 
                   processor->gpr[getR2(instruction)]) 
                { processor->pc += getImmediateValue(instruction) * 4;};
                break;
                  
    case BGE  : if (checkBrachInstructionIsValid(instruction,processor)==0) 
                return 0;
                if (processor->gpr[getR1(instruction)] >= 
                   processor->gpr[getR2(instruction)]) 
                { processor->pc += (getImmediateValue(instruction) * 4);};
                break;
                  
    case JMP  : if (checkJtypeIsValid(instruction)==0) return 0;
                processor->pc = getAddress(instruction);
                break;
                  
    case JR   : if (checkRtypeInstructionIsValid(instruction)==0) return 0;
                processor->pc = getRegisterValue
                  (processor, getR1(instruction));
                break;
                  
    case JAL  : if (checkJtypeIsValid(instruction)==0) return 0;
                processor->gpr[31] = processor->pc + sizeof(uint32_t); 
                processor->pc = getAddress(instruction);
                break;
                  
    case OUT  : if (checkRtypeInstructionIsValid(instruction)==0) return 0;
                printf("%c", (char)getRegisterValue
                  (processor, getR1(instruction)));
                break;
                  
    case DIV  : if (checkRtypeInstructionIsValid(instruction)==0) return 0;
                division = div(getRegisterValue(processor,getR2(instruction))
                            ,getRegisterValue(processor,getR3(instruction)));
                processor->gpr[getR1(instruction)] = division.quot;
     
    case DIVI : if (checkItypeInstructionIsValid(instruction)==0) return 0;
                division = div(getRegisterValue(processor,getR2(instruction))
                            ,getImmediateValue(instruction));
                processor->gpr[getR1(instruction)] = division.quot;
      
    case MOD  : if (checkRtypeInstructionIsValid(instruction)==0) return 0;
                division = div(getRegisterValue(processor,getR2(instruction))
                            ,getRegisterValue(processor,getR3(instruction)));
                processor->gpr[getR1(instruction)] = division.rem;
      
    case MODI : if (checkItypeInstructionIsValid(instruction)==0) return 0;
                division = div(getRegisterValue(processor,getR2(instruction))
                            ,getImmediateValue(instruction));
                processor->gpr[getR1(instruction)] = division.rem;
      
    case FACT : if (checkRtypeInstructionIsValid(instruction)==0) return 0;
                processor->gpr[getR1(instruction)] = 
                getRegisterValue(processor, getR2(instruction));
                for(int i = 1; i<processor->gpr[getR2(instruction)] ; i++) {
                  processor->gpr[getR1(instruction)] = 
                    (getRegisterValue(processor, getR1(instruction)))*
                    (getRegisterValue(processor, getR2(instruction))-i);
                }
                break;
      
    case FACTI: if (checkItypeInstructionIsValid(instruction)==0) return 0;
                processor->gpr[getR1(instruction)] = 
                getImmediateValue(instruction);
                for(int i = 1; i<getImmediateValue(instruction) ; i++) {
                  processor->gpr[getR1(instruction)] = 
                    (getRegisterValue(processor, getR1(instruction)))*
                    (getImmediateValue(instruction)-i);
                }
                break;
      
    case SWAP : if (checkRtypeInstructionIsValid(instruction)==0) return 0;
                temp = 
                  getRegisterValue(processor, getR1(instruction));
                processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction));
                processor->gpr[getR2(instruction)] = temp;
                break;
  }
  if(processor->pc == backupPC)  processor->pc += sizeof(uint32_t);
  return 1;
}

void step(struct Processor *proc) {
  if (programExitValue==1) {
    printf("No programs running currently. The previous program has exited already so step cannot be executed\n");
    return;
  }
  int retVal = carryOutInstruction(proc);
  if (retVal==0) {
    programExitValue= 1;
    printf("\n\nProgram exited normally.\n");
  }
}

char *removeSpace(char *str) {
  while(*str) {
    if (isspace((int) *str)==0) return str;
    str++;
  }
  return str;
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

void listInstruction(char *filepath, int n) {
  FILE *fp;
  fp = fopen(filepath,"r");
  char *buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
  if (fp==NULL) {
    perror("ERROR in opening file");
    exit(EXIT_FAILURE);
  }
  while (!feof(fp) &&0<n ){
    memset(buffer, 0, ((sizeof(char))*BUFFER_SIZE));
    fgets (buffer, BUFFER_SIZE, fp); 
    if(strlen(buffer)>1) n--;
    //printf("%s------n=%i----length =%i\n", buffer,n,strlen(buffer));
    
  }
  if(n==0) {
    printf("%s", removeSpace(buffer));
  }
  else{
    perror("End of file reached before line");
  }                  
  free(buffer);
  fclose(fp);
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
  FILE *fp;
  fp = fopen("welcomeMessage.txt","r");
  char *buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
  if (fp==NULL) {
    perror("ERROR in opening file");
    exit(EXIT_FAILURE);
  }
  while (!feof(fp)){
    memset(buffer, 0, ((sizeof(char))*BUFFER_SIZE));
    fgets (buffer, BUFFER_SIZE, fp); 
    printf("%s",buffer);    
  }
}

int checkUserCommandIsValid(char *command) {
  for (int i=0; i<NUMBER_OF_COMMANDS; i++) {
    if (strcmp(command,debugInstructions[i])==0) return 1;
  }
  return 0;
}

char **getUserCommand(void) {
  printf("(JVG)");
  char *buff = malloc(BUFFER_SIZE);
  fgets(buff,BUFFER_SIZE,stdin);
  char *ptr = malloc(2);
  if( (ptr = strchr(buff, '\n')) != NULL) *ptr = '\0';
  char **tokens = malloc(sizeof(char) * BUFFER_SIZE);
  tokens = tokeniseUserCommand(buff);
  if (checkUserCommandIsValid(tokens[0])) return tokens;
  printInvalidCommandMessage();
  return getUserCommand();
}

int confirmToQuit() {
  printf("Are you sure you want to quit? enter y for yes and n for no\n(JVG)");
  char *ans = malloc(sizeof(char) * BUFFER_SIZE);
  fgets(ans,sizeof(char) * BUFFER_SIZE, stdin);
  char *ptr = ans;
  if( (ptr = strchr(ans, '\n')) != NULL) *ptr = '\0';
  int ret = strcmp(ans,"y")==0;
  if (ret==0 && strcmp(ans,"n")!=0) {
    free(ans);
    printf("Please enter a valid answer\n");
    return confirmToQuit();
  } 
  free(ans);
  return ret;
}
 
 
void run(struct Processor *proc,int *breakPoints) {
  if (programExitValue==1) {
      printf("No programs running currently. The previous program has exited already so step cannot be executed\n");
      return;
  }
  int retVal = 1;
  
  do {
    retVal = carryOutInstruction(proc);  
  } while (retVal && !checkIfBreakPoint(breakPoints,(proc->pc/4)+1));
  if (programExitValue==1) return;
  if (checkIfBreakPoint(breakPoints,((int) proc->pc/4)+1)==1) {
    printf("Breakpoint reached.\n");
    return;
  }
  fflush(stdout);
  dumpProcessor(proc);
  programExitValue = 1;
  printf("\nProgram exited normally.\n");
}

void setBreakPoints(int *breakPoints,char **tokens) {
  int *temp = malloc(sizeof(int) * BREAKPOINTS_ARRAY_SIZE);
  int i=0;
  while(*tokens) {
    if (checkIfNumber(*tokens)==0) {
      printInvalidCommandMessage();
      return;
    }
    temp[i] = atoi(*tokens);
    i++;
    tokens++;
  }
  memcpy(breakPoints,temp,sizeof(int) * i);
  free(temp);
}

int executeUserCommand(char *assembly, char *bin, struct Processor *proc, char **tokens, int *breakPoints) {
  if (strcmp(tokens[0], "reg")==0) {
    tokens++;
    printReg(proc, tokens);
    return 0;
  } else if (strcmp(tokens[0], "mem")==0) {
    tokens++;
    printMemory(proc, tokens);
    return 0;
  } else if (strcmp(tokens[0], "pc")==0) {
    printPC(proc);
    return 0;
  } else if (strcmp(tokens[0], "search")==0) {
    tokens++;
    search(proc, tokens);
    return 0;
  } else if (strcmp(tokens[0], "stp")==0) {
    step(proc);
    return 0;
  } else if (strcmp(tokens[0], "list")==0) {
    listInstruction(assembly, ((proc->pc)/4)+1);
    return 0;
  } else if (strcmp(tokens[0], "--help")==0) {
    system("cat help.txt | less");
    return 0;
  } else if (strcmp(tokens[0], "run")==0) {
    run(proc,breakPoints);
    return 0;
  } else if (strcmp(tokens[0],"q")==0) {
    return confirmToQuit();
  } else if (strcmp(tokens[0],"break")==0) {
    setBreakPoints(breakPoints,tokens+1);
    return 0;
  }
  return 0;
}

int main(int argc, char **argv) {
  struct Processor *proc = malloc(sizeof(struct Processor));
  assert("There are wrong number of arguents given" && argc==3);
  char *fBin = argv[2];
  char *fAssembly = argv[1];
  memset(proc,0,sizeof(struct Processor));
  binaryFileLoader(fBin,proc);
  system("clear");
  int *breakPoints = malloc(sizeof(int) *BREAKPOINTS_ARRAY_SIZE);
  memset(breakPoints,-1,sizeof(int) *BREAKPOINTS_ARRAY_SIZE);
  printWelcomeMessage();
  char **tokens = malloc(sizeof(char) *BUFFER_SIZE);
  int returnVal = 0; 
  do {
    tokens = getUserCommand();
    returnVal = executeUserCommand(fAssembly,fBin,proc,tokens,breakPoints);
  } while (!returnVal);
  printf("Thanks for using JVG debugger\n");
  system("clear");
  free(proc);
  free(breakPoints);
  return EXIT_SUCCESS;
}
