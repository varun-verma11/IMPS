#include "assemble.h"
#include <string.h>

#define ASCII_FOR_COLON 58

int checkLabel(char *instruction) {
  return strchr(instruction,58)!=NULL ;
}

void tokeniserWithoutLabel(char *instruction,char *tokens[5]) {
  char *token;
  int count =1;
  token = strtok(instruction, " ");
  tokens[count] = token;
  do {
    count++;
    token = strtok(NULL, " ");
    tokens[count] = token;
  } while (count!=5);
}

void tokeniserWithLabel(char *instruction,char *tokens[5]) {
  char *token;
  int count =0;
  token = strtok(instruction, ":");
  do {
    tokens[count] = token;
    token = strtok(NULL, " ");
    count++;
  } while (count!=5);
}

void tokeniser(char *instruction, char *tokens[5]) {
  if(checkLabel(instruction)) {
    tokeniserWithLabel(instruction,tokens);
  } else {
    tokeniserWithoutLabel(instruction,tokens);
  }
}

int main(void) {
  char ins[] = "label: add $1 $2 $3";
  char *tokens[5];
  int count = 0;
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
  tokeniser(ins,tokens);  
  while (count!=5) {
    printf("token %i --> %s \n",count,tokens[count]);
    count++;
  }
  return EXIT_SUCCESS;
}
