#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

struct Table_Elem {
  int value;
  struct Table_Elem *next;
  char *key;
};

struct Table {
  struct Table_Elem *head;
};

void addToTable(char *key, int value, struct Table *table) {
  struct Table_Elem new_elem;
  new_elem.key = key;
  new_elem.value = value;
  new_elem.next = table->head;
  table->head = &new_elem;
}

int getValue(char *key, struct Table *table) {
  struct Table_Elem *current = table->head;
  
  while(current!=NULL) {
    if (strcmp(key,current->key)==0) return current->value;
    current = current->next;
  }
  return -1;
}

struct Table *initialiseSymbolTable(void) {
  struct Table *table= malloc(sizeof(struct Table));
  table->head = NULL;
  addToTable("halt",0,table);
  return table;
}

int main(void) {
  struct Table *symbolTable = initialiseSymbolTable();
  printf("halt  ----> %d \n",getValue("halt",symbolTable));
  return EXIT_SUCCESS;
}
