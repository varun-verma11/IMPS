#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

struct ListElem {
  int numberOfElem;
  struct ListElem *next;
  struct ListElem *prev;
  char *command;
};

struct DLLIST {
  struct ListElem *start;
  struct ListElem *end;
  struct ListElem *current;
};


void addToList(char *key, int value, struct Processor *proc) {

}

int getValue(char *key, struct Table *table);
