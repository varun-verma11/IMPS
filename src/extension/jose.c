
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
  int start = 0 ;
  int end = NUMBER_OF_REGISTERS;
  if(!checkRegCommandIsValid(tokens+1)){
    printInvalidCommandMessage();
    return;
  }
  if (strcmp("-r",tokens[0])==0) {
    start = getRegisterNumber(tokens[1]);
    end   = getRegisterNumber(tokens[2]);
  }
  else if (strcmp("-m",tokens[0])==0) {
    tokens++;
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
  char *fp = malloc(BUFFER_SIZE);
  fp = "assemble.c";
  printLine(fp,2000);
  return 0;
}
