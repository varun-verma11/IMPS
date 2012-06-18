#include "debugger.h"


void printInvalidCommandMessage(void) {
  printf("Invalid command. Please enter --help for help\n");
}

void printPC( struct Processor *proc) {
  printf("PC = %i \n",proc->pc);
}


void printSegmentationFaultMessage(void) {
  printf("Executing the current line would cause segmentation fault.\n");
  printf("Please use the 'list' command to track the line where the error occurred\n");
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

