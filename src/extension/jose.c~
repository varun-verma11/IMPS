#include "jose.h"

#define NUMBER_OF_REGISTERS 32
#define MEMORY_SIZE 65536

struct Processor {
  uint32_t pc;
  int32_t gpr[NUMBER_OF_REGISTERS];
  uint8_t memory[MEMORY_SIZE]; 
};	 
int checkRegister(char *token){
 return (token!=NULL) ? (token[0]=='$') : 0;
}
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

int checkAllRegistersAreValid(char **regs) {
  while (*regs) {
    if (!checkRegister(*regs) || !checkIfNumber(*regs+1) || 
              getRegisterNumber(regs) <0 || 
              getRegisterNumber(regs) >= NUMBER_OF_REGISTERS) {
      return 0;
    }
    regs++;
  }
  return 1;
}

void printInvalidCommandMessage(void) {
  printf("(JVG) invalid command. Please enter --help for help\n (JVG)");
}



void printLine(char *filepath, int n){
  /*
  basically this doesnt has any checks for empty lines...inlude that check and check if its an empty line and dont use a variable iin this..use n the param given in and decrement it everytime if u dont read an empty line. and then only print it on the screen coz ryt now its prtinting empty line and also keep the print format as it is..only the loop should be changed not the print statement.
  
  */
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
    printf("%s", buffer);
  }
  else{
    perror("End of file reached before line");
  }                  
  free(buffer);
  fclose(fp);

}
/*



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
*/
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





int main(void){



return 0
}

