#include "debugger.h"

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

void step(struct Processor *proc) {
  carryOutInstruction(proc);
  printf("(JVG) ");
}

void printReg(struct Processor *proc , char **tokens) {
  if (strcmp("-r",tokens[0])==0) {
    int end = getRegisterNumber(tokens[2]);
    for (int i=start; i<end/4 ; i++) {
      for (int j=0;j<4 ; j++) {
        printf("$%s = %i \t",(i*j) + j,getRegisterValue(proc,(i*j) + j));
      }
      printf("      \n");
    }
  } else if (strcmp("-a",tokens[0])==0) {
    for (int i=0; i<NUMBER_OF_REGISTERS/4 ; i++) {
      for (int j=0;j<4 ; j++) {
        printf("%s = %i \t",tokens[(i*j) + j],getRegisterValue(proc,getRegisterNumber(tokens[(i*j) + j])));
      }
      printf("      \n");
    }
  } else {
    int i =0;
    int j=0;
    while(tokens[i]!=NULL) {
      printf("%s = %i \t",tokens[i],getRegisterValue(proc, getRegisterNumber(tokens[i])));
      i++;
      j++;
      if (j==4) printf("      \n");
    }
    printf("\n (JVG)");    
  }
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

void printPC( struct Processor *proc) {
  printf("(JVG) PC = %x \n (JVG)",proc->pc);
}

void printMemory(struct Processor *proc, char **tokens) {
  if (strcmp("-r",tokens[0])==0) {
    int end = getRegisterNumber(tokens[2]);
    for (int i=0; i<end/4 ; i++) {
      for (int j=0;j<4 ; j++) {
        printf("%s = %i \t",tokens[(i*j) + j],getRegisterValue(proc,getRegisterNumber(tokens[(i*j) + j])));
      }
      printf("      \n");
    }
  } else if (strcmp("-a",tokens[0])==0) {
    for (int i=0; i<MEMORY_SIZE/4 ; i++) {
      for (int j=0;j<4 ; j++) {
        printf("%s = %i \t",(i*j)+j,getRegisterValue(proc,getRegisterNumber((i*j) + j)));
      }
      printf("      \n");
    }
  } else {
    int i =0;
    int j=0;
    while(tokens[i]!=NULL) {
      printf("%s = %i \t",tokens[i],getRegisterValue(proc, getRegisterNumber(tokens[i])));
      i++;
      j++;
      if (j==4) printf("      \n");
    }
    printf("\n (JVG)");    
  }
}

void printWelcomeMessage(void){
  printf("Welcome to JVG debugger for binary programs for IMPS instruction set. \n Please type the specific commands for the task or enter --help  for help.");
}

int checkUserCommandIsValid(char *command) {
  for (int i=0; i<NUMBER_OF_COMMANDS; i++) {
    if (strncmp(command,debugInstructions[i],sizeof(char)*strlen(debugInstructions[i]))==0) return 1;
  }
  return 0;
}

char *getUserCommand(void) {
  printf("(jvg)");
  char *buff = malloc(BUFFER_SIZE);
  fgets(buff,BUFFER_SIZE,stdin);
  if (checkUserCommandValid(buff)) return buff;
  printf("(jvg) INVALID COMMAND: Please enter a valid command or type '--help' for help");

  /*--------------------------------------------
  
  CHECK IF  RECURSION IS OK OR SHOULD I HAVE A
  
  LOOP.
  
  --------------------------------------------*/
  
  return getUserCommand();
}

/*
  This method carries out the execution of the binary code in the file specified
  by the arguments at run time. The file is loaded into the memory of the
  structure processor and then the execution is carried out in the while loop.
  The execution of terminates when an instruction with opcode HALT is reached.
  @param argv : this specifies the arguements which were given through the
                terminal when the program was run.
  @param argc : this specifes the number of arguments provided
  @return     : the method returns 0 when the method executes without any errors
*/
int main(int argc, char **argv) {
  assert("There are wrong number of arguents given" && argc==2);
  struct Processor processor;
  char *filepath = argv[1];

  memset(&processor, 0, sizeof(struct Processor));

  

  binaryFileLoader(filepath, processor);
    
  while (getInstructionAtPC(processor)) {

  }
  
  fflush(stdout);

  dumpProcessor(&processor);

  return EXIT_SUCCESS;
}
