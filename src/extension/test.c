
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MIN(a, b) (a > b ? b : a)

#define MEMORY_SIZE 65536
#define NUMBER_OF_REGISTERS 32
#define NUMBER_OF_COMMANDS 8
#define BUFFER_SIZE 300   


void executeUserCommand(char *bin, char **tokens) {
  printf("\n token 0 --> %s \n",tokens[0]);
  if (strcmp(tokens[0], "reg")==0) {
    tokens++;
    //printReg(proc, tokens);
    printf("reg\n");
  }
  else if (strcmp(tokens[0], "mem")==0) {
    tokens++;
    //printMemory(proc, tokens);
    printf("mem\n");
  }
  else if (strcmp(tokens[0], "pc")==0) {
    //printPC(proc);
    printf("pc\n");
  }
  else if (strcmp(tokens[0], "search")==0) {
    tokens++;
   // search(proc, tokens);
   printf("search\n");
  }
  else if (strcmp(tokens[0], "stp")==0) {
    //step(proc);
    printf("stp\n");
  }
  else if (strcmp(tokens[0], "list")==0) {
    //printLine(assembly, ((proc->pc)/4)+1);
    printf("list\n");
  }
  else if (strcmp(tokens[0], "--help")==0) {
    system("cat help.txt | less");
  } else if (strcmp(tokens[0], "run")==0) {
    printf("run \n");
    char cmd[] = "./emulate ";
    *cmd = *strcat(cmd,bin);
    printf("%s\n",cmd);
    system(cmd);
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

int main(void) {
  char *fp = "simple.bin";
  char **tokens = malloc(300);
  //char *cmd = malloc(100);
  char cmd[] = "run";
  tokens = tokeniseUserCommand(&cmd);
  executeUserCommand(fp,tokens);
  return 1;
}


