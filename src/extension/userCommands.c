#include "emulate.h"
#include "parser.h"
#include "userCommands.h"
#include "carryOutInstruction.h"

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
    printf("(JVG)> %s (JVG)>", buffer);
  }
  else{
    perror("End of file reached before line");
  }                  
  free(buffer);
  fclose(fp);

}

void printReg(struct Processor *proc , char **tokens) {
  int start = 0 ;
  int end = NUMBER_OF_REGISTERS;
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
    int j=0;
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
  for (int i=start; i<end/8 ; i++) {     
    for (int j=0;j<8 ; j++) {
      printf("%s = %i \t",tokens[(i*j) + j],getRegisterValue(proc,getRegisterNumber(tokens[(i*j) + j])));
    }
    printf("      \n");
  }  
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
      printf("$%i=%i  ",i,getRegisterValue(getRegisterNumber));
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

void printMemory(struct Processor *proc, char **tokens) {
  int start = 0;
  int end = MEMORY_SIZE;
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
  int end = MEMORY_SIZE;
  if (!checkIfAllMemoryLocationsAreValid(tokens+1)) {
    printInvalidCommandMessage();
    return;
  }
  int value = atoi(tokens[1]);
  if (strcmp(tokens[0],"-r")==0) {
    start = getRegisterNumber(token[2]);
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

