#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

/*
  This structure defines a element in the table. Each element in the structure
  table contains a unique key and a value and pointer to the next element in the
  table.  
*/
struct Table_Elem {
  int value;
  struct Table_Elem *next;
  char *key;
};

/*
  this structure specifes the ADT table which points at the first, i.e. head of
  the table  
*/
struct Table {
  struct Table_Elem *head;
};

void addToTable(char *key, int value, struct Table *table);
int getValue(char *key, struct Table *table);
struct Table *initialiseEmptyTable(void);
struct Table *initialiseOpcodeTable(void);

#endif

