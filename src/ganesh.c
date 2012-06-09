#include "assemble.h"
#include <string.h>

#define ASCII_FOR_COLON 58

void tokeniser(char *instruction,char *tokens[4]) {
  char *token;
  int count =0;
  token = strtok(instruction, ":");
  do {
    token = strtok(NULL, " ");
    tokens[count] = token;
    count++;
  } while (count!=5);
}

char *getLabel(char *instruction) {
  return (strchrnul(instruction,58)!=NULL) ? strtok(instruction,":") : NULL;
}

int main(void) {
  char ins[] = "add $1 $2 $3";
  char *tokens[4];
  /*
  static char ip_addr[] = "label: add $1 $2 $3";
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
  printf ("Done.\n\n\n\");
  */
  
  char *inscpy = malloc(sizeof(ins));
  inscpy = strcpy(inscpy,ins);
  
  int count =0;
  printf("label   ---> %s \n",getLabel(inscpy));
  tokeniser(ins,tokens);  
  while (count!=4) {
    printf("token %i --> %s \n",count,tokens[count]);
    count++;
  }
  return EXIT_SUCCESS;
}
