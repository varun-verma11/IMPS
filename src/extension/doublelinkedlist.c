#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

struct ListElem {
  struct ListElem *next;
  struct ListElem *prev;
  struct Processor *proc;
};

struct DLLIST {
  int numberOfElem;
  struct ListElem *start;
  struct ListElem *end;
  struct ListElem *current;
  int numberOfMaxElem ;
};


void 
