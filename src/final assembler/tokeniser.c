#include "assemble.h"

/*
  This method check if a label exists in the given instruction.
  @param instruction : specifies the instruction in which it has to be checked 
                       if a label exists  
  @return            : returns value 1 if label does not exists
*/
int checkLabelExists(char *instruction) {
  //58 is the ascii value for ':'
  return strchr(instruction,58)!=NULL ;
}

/*
  This method tokenises an instruction which does not contain a label
  @param instruction : specifies the instruction which has to be tokenised
  @param tokens      : specifies the array in which the tokens have to be stored
*/
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

/*
  This method tokenises an instruction which contains a label
  @param instruction : specifies the instruction which has to be tokenised
  @param tokens      : specifies the array in which the tokens have to be stored
*/
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

/*
  This method tokenises a given instruction after checking if the instruction 
  contains a label or not
  @param instruction : specifies the instruction which has to be tokenised
  @param tokens      : specifies the array in which the tokens have to be stored
*/
void tokeniser(char *instruction, char *tokens[5]) {
  char *inscpy = (char *) malloc(sizeof(char) * strlen(instruction));
  inscpy =strcpy(inscpy,instruction);
  if(checkLabelExists(inscpy)) {
    tokeniserWithLabel(inscpy,tokens);
  } else {
    tokeniserWithoutLabel(inscpy,tokens);
  }
}
