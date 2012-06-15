#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

struct ListElem {
  int numberOfElem;
  struct ListElem *next;
  struct ListElem *prev;
  struct ListElem *current;
  char *command;
};

struct DLLIST {
  struct ListElem *start;
  struct ListElem *end;
};


void addToList(char *key, int value, struct Table *table);
int getValue(char *key, struct Table *table);
