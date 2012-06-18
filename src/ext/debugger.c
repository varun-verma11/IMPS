#include "debuggerChecks.h"
#include "carryOutInstructionForExtension.h"
#include "searchAndPrintRegMem.h"
#include "debugger.h"

//this is a global constant to store the state of the program, i.e. value 1 if program ran.
int programExitValue;


void printInvalidCommandMessage(void) {
  printf("Invalid command. Please enter --help for help\n");
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



void printPC( struct Processor *proc) {
  printf("PC = %i \n",proc->pc);
}




void printSegmentationFaultMessage(void) {
  printf("Executing the current line would cause segmentation fault.\n");
  printf("Please use the 'list' command to track the line where the error occurred\n");
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
  int i=0;
  if (strcmp(tokens[0],"-r")==0) {
    tokens++;
    while(*tokens) {
      if (checkIfNumber(*tokens)==0) {
        printInvalidCommandMessage();
        return;
      }
      if (breakPoints[i]==atoi(*tokens)) {
        breakPoints[i] = -1;
      };
      if (breakPoints[i] ==-1) {
        printInvalidCommandMessage();
        printf("breakpoint does not exists");
        return;
      }
      i++;
      tokens++;
    }
  } else if (strcmp(tokens[0],"-a")==0) {
    tokens++;
    int *temp = malloc(sizeof(int) * BREAKPOINTS_ARRAY_SIZE);
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
    free(tokens);
  } while (!returnVal);
  printf("Thanks for using JVG debugger\n");
  system("clear");
  free(proc);
  free(breakPoints);
  return EXIT_SUCCESS;
}
