#include "assemble.h"
int checkLabelExists(char *instruction) {
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
  char *inscpy = (char *) malloc(sizeof(char) * strlen(instruction));
  inscpy =strcpy(inscpy,instruction);
  if(checkLabelExists(inscpy)) {
    tokeniserWithLabel(inscpy,tokens);
  } else {
    tokeniserWithoutLabel(inscpy,tokens);
  }
}

char *getLabel(char *instruction) {
  char *inscpy = (char *) malloc(sizeof(instruction));
  inscpy =strcpy(inscpy,instruction);
  return strtok(inscpy,":");
}
