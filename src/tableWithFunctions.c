#include "assemble.h"

void addToTable(char *key, int value, uint32_t (*parser) (char **, struct Table *),struct Table *table) {
  struct Table_Elem *new_elem = (struct Table_Elem *) malloc(sizeof(struct Table_Elem));
	new_elem->key = key;
  new_elem->value = value;
  new_elem->parser = parser; 
  new_elem->next = table->head;
  table->head = new_elem;
}

int getValue(char *key, struct Table *table) {
  struct Table_Elem *current = table->head;  
  while(current!=NULL) {
    printf("key   ----> %s     Value ----> %d \n",current->key,current->value);
    if (strcmp(key,current->key)==0) return current->value;
    current = current->next;
  }
  return -1;
}

struct Table *initialiseSymbolTable(void) {
  struct Table *table = (struct Table *) malloc(sizeof(struct Table));
  table->head = NULL;
  uint32_t (*parserI) (char **, struct Table *) = &parser_i;
  uint32_t (*parserJ) (char **, struct Table *) = &parser_j;
  uint32_t (*parserR) (char **, struct Table *) = &parser_r;
  uint32_t (*parserHalt) (char **, struct Table *) = &parser_halt;
  addToTable("halt",0,parserHalt,table);
  addToTable("add", 1,parserR,table);
  addToTable("addi",2,parserI,table);
  addToTable("sub",3,parserR,table);
  addToTable("subi",4,parserI,table);
  addToTable("mul",5,parserR,table);
  addToTable("muli",6,parserI,table);
  addToTable("lw",7,parserI,table);
  addToTable("sw",8,parserI,table);
  addToTable("beq",9,parserI,table);
  addToTable("bne",10,parserI,table);
  addToTable("blt",11,parserI,table);
  addToTable("bgt",12,parserI,table);
  addToTable("ble",13,parserI,table);
  addToTable("bge",14,parserI,table);
  addToTable("jmp",15,parserJ,table);
  addToTable("jr",16,parserR,table);
  addToTable("jal",17,parserJ,table);
  addToTable("out",18,parserR,table);
  return table;
}
