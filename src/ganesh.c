#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void tokeniser(char instruction[], char **token) {

  char *buf_pp = NULL;
  char *s;
  int count =0;
    
  /* Parse the first argument */
  token[count] = strtok_r(instruction, ":", &buf_pp);
  do {
    /* Increment count */
    count++;
    /* Get the next token until end of string */
    token[count] = strtok_r(NULL, " ", &buf_pp);
  } while (token[count]!=NULL);
}

