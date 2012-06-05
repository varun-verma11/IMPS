#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

struct Table_elem {
  void *value;
  struct table_elem *next;
  char key[];
};

struct Table {
  int number_of_elems;
  struct table_elem *head; 
};

void add_to_table(char key[], void *value, struct Table *table) {
  struct Table_elem new_elem /*= malloc(sizeof(struct Table_elem))*/;
  new_elem.value = value;
  new_elem.next = &(*(table->head)->next);
  new_elem.key = key;
  table->head->next = &new_elem;
  table->number_of_elems += 1;
}

void *getValue(struct table_elem *head, char key[]) {
  struct table_elem current = head;  
  while(current!=NULL) {
    if (!strcmp((current->key),key)) {
      return &(current->value);
    }
    current = current.next;
  }
  return NULL;
}

void parser_j(void) {
}

void parser_r(void) {
}

void parser_i(void) {
}

struct Table *initialise_table(void) {
  struct Table_elem elem = malloc(sizeof(" ") + sizeof(0) + sizeof(struct *Table_elem));
  elem.next = NULL;
  elem.key = " ";
  elem.value = 0;
  struct Table table;
  table.head = elem;
  table->number_of_elems += 1;
  add_to_table("halt",0,&table);
  add_to_table("add",1,&table);
  add_to_table("addi",2,&table);
  add_to_table("sub",3,&table);
  add_to_table("subi",4,&table);
  add_to_table("mul",5,&table);
  add_to_table("muli",6,&table);
  add_to_table("lw",7,&table);
  add_to_table("sw",8,&table);
  add_to_table("beq",9,&table);
  add_to_table("bne",10,&table);
  add_to_table("blt",11,&table);
  add_to_table("bgt",12,&table);
  add_to_table("ble",13,&table);
  add_to_table("bge",14,&table);
  add_to_table("jmp",15,&table);
  add_to_table("jr",16,&table);
  add_to_table("jal",17,&table);
  add_to_table("out",18,&table);
  add_to_table("f_for_r_type", &parser_r, &table);
  add_to_table("f_for_j_type", &parser_j, &table);
  add_to_table("f_for_i_type", &parser_i, &table);  
  table->number_of_elems += 22;
}

