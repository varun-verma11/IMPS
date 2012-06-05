#include <stdlib.h>
#include <string.h>
#include <stdio.h>


  char **tokeniser(char *instruction) {
  /*
  This should return an array of strings, splitting up the instructions into
  tokens. Tokens should cover labels (the first piece of text ending in a 
  colon ":"), operations (such as add, addi, mul, muli, etc) and operands (such
  as the registers where data is found and stored or the immediate values to be
  used). 
  
  issue: Should I further split them into operand types, ie explicitly state if 
  it's a register, constant or address?)
  */
  
  int i;
  char *str1, *token;
  char *saveptr1;
  char **tokens;
  char labelTokenDelim[] = ": ";
  char opTokenDelim[] = " ";
  
  
  for (i = 0, str1 = instruction; ;i++, str1 = NULL) {
    token = strtok_r(str1, labelTokenDelim, &saveptr1);
    if (token == NULL) break;
    tokens[i] = token;
    printf("%s\n", token);
  }
  for (str1 = instruction; ;i++, str1 = NULL) {
    token = strtok_r(str1, opTokenDelim, &saveptr1);
    if (token == NULL) break;
    tokens[i] = token;
    printf("%s\n", token);
  }
  return tokens;
 
}

int main(void) {
  char ins[] = "Label: addi $31 $32 32";
  char instructionPtr = *ins;
  char **tokens = tokeniser(&instructionPtr);
  int i;
  for(i = 0; ;i++) {
    while(tokens[i] != NULL) {
      printf("%s\n", tokens[i]);
    }
  }
  return 0;
}
