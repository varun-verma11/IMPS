#include <stdlib.h>
#include <string.h>
#include <stdio.h>



int main(void) {
  //char **token = (char **) malloc(sizeof(char *) *5);
  
  static char ip_addr[] = "label: add $1 $2 $3";
  char *buf_pp = NULL;
  char *s = NULL;
  int count = 0;

  s = strtok_r (ip_addr, ":", &buf_pp);

  while (s) {
    /* Increment count */
    count++;

    /* Print the current token */
    printf ("token[%d]: %s\n",
    count, s);

    /* Get the next token until end of string */
    s = strtok_r (NULL, " ", &buf_pp);
  }
  printf ("Done.\n");
  
  //tokeniser(ins); 
  return EXIT_SUCCESS;
}
