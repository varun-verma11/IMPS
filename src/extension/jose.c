
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

int main(void){
  char *fp = malloc(BUFFER_SIZE);
  fp = "assemble.c";
  printLine(fp,2000);
  return 0;
}

