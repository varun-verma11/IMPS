#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char **tokeniser(char *instruction) {

  printf("%s \n",instruction);
  //http://www.linuxquestions.org/questions/programming-9/question-about-strtok_r-built-in-function-in-c-181144/
  //http://www.kirupa.com/forum/archive/index.php/t-233004.html
  char *buf_pp = NULL;
  char *s;
  int count =0;
  char **token = malloc(sizeof(char*)*3);
  //printf("size of tokens  ->  %d \n",(sizeof(token)));
  printf("check 2\n");
    
  /* Parse the first argument */
  token[count] = strtok_r(&instruction, ":", &buf_pp);
  do {
    /* Print the current token */
    printf ("token  -> %s \n", token[count]);
    /* Increment count */
    count++;
    /* Get the next token until end of string */
    token[count] = strtok_r(NULL, " ", &buf_pp);
  } while (token[count-1]!=NULL);
  /* Done */
  printf ("Done.\n");
  return token;
}

int main(void) {

  char **tokens = tokeniser("label: addi $1 $23 32");  
  
  return 0;
}
