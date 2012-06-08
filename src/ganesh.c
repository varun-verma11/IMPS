#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void tokeniser(char *instruction, char **tokens) {
  char *buf_pp = NULL;
  int count =0;
  tokens[count] = strtok_r(instruction, ":", &buf_pp);
  do {
    printf("token --> %s \n",tokens[count]);
    count++;
    tokens[count] = strtok_r(NULL, " ", &buf_pp);
  } while (tokens[count]!=NULL);
  printf("token --> %s \n",tokens[count]);
}

int main(void) {
  //char **token = (char **) malloc(sizeof(char *) *5);
  
  static char ip_addr[] = "label: add $1 $2 $3";
  char *buf_pp = NULL;
  char *s = NULL;
  int count = 0;

  s = strtok_r (ip_addr, ":", &buf_pp);

  while (s) {
    count++;
    printf ("token[%d]: %s \n", count, s);
    s = strtok_r (NULL, " ", &buf_pp);
  }
  printf ("Done.\n");
  
  //tokeniser(ins); 
  return EXIT_SUCCESS;
}
