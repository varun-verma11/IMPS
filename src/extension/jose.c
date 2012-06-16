
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define BUFFER_SIZE 300
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
  if (strcmp("-r",tokens[0])==0) {
    if((checkAllRegistersAreValid(char tokens++))){
      int end = getRegisterNumber(tokens[2]);
      for (int i=start; i<end/4 ; i++) {
        for (int j=0;j<4 ; j++) {
          printf("$%s = %i \t",(i*j) + j,getRegisterValue(proc,(i*j) + j));
        }
      printf("      \n");
      }
   }else{printInvalidCommandMessage()};
  } else if (strcmp("-a",tokens[0])==0) {//not sure about i and j....    
        for (int i=0; i<NUMBER_OF_REGISTERS/4 ; i++) {     
          for (int j=0;j<4 ; j++) {
           printf("%s = %i \t",tokens[(i*j) + j],getRegisterValue(proc,getRegisterNumber(tokens[(i*j) + j])));
          }
        printf("      \n");
        }
       
  } else {
    int i =1;
    int j=0;
    while(tokens[i]!=NULL) {
      for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++) {//check if registers are valid!!!
       int reg = i * 8 + j;
      printf("%s = %i \t",tokens[i],getRegisterValue(proc, getRegisterNumber(tokens[i])));
      i++;
      j++;
      if (j==4) printf("      \n");
    }
    printf("\n (JVG)");    
  }
}





int main(void){
  char *fp = malloc(BUFFER_SIZE);
  fp = "assemble.c";
  printLine(fp,2000);
  return 0;
}

