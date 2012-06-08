#include "assemble.h"

void tokeniser(char *instruction, char **tokens) {
  char *buf_pp = NULL;
  char *labelDelim = ":";
  int count =0;
  tokens[count] = strtok_r(instruction,":" , &buf_pp);
  do {
    printf("token --> %s \n",tokens[count]);
    count++;
    tokens[count] = strtok_r(NULL, " ", &buf_pp);
  } while (tokens[count]!=NULL);
}


int main(void) {
  char **token = malloc(sizeof(char *) *5);
  
  static char ip_addr[] = "label: add $1 $2 $3";
  char *ins = "label: add $1 $2 $3";
  static char inst[] = *ins;
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
  
  tokeniser(inst, token); 
  return EXIT_SUCCESS;
}
