#include "table.h"

/*
  This method adds the given key and value to the ADT table which is specifed
  @param key   : specifies the key to be added to the table
  @param value : specifies the value to be added to the table
  @param table : specifies the table in which the given key and values have to 
                 be added
*/
void addToTable(char *key, int value, struct Table *table) {
  struct Table_Elem *new_elem = (struct Table_Elem *) malloc(sizeof(struct Table_Elem));
	new_elem->key = key;
  new_elem->value = value;
  new_elem->next = table->head;
  table->head = new_elem;
}

/*
  This method returns the value for the given key in the given table.
  @param key   : specifies the key whose value has to be returned
  @param table : specifes the table from which the value of the given table has
                 to be returned
  @return      : this method retunrs the value for the given key in the table 
                 given
*/
int getValue(char *key, struct Table *table) {
  struct Table_Elem *current = table->head;  
  while(current!=NULL) {
    if (strncmp(key,current->key,sizeof(char) * strlen(current->key))==0) {
      return current->value;
    }
    current = current->next;
  }
  free(current);
  return -1;
}

/*
  This method initialies an empty table
  @return : the method returns a pointer for an empty table.  
*/
struct Table *initialiseEmptyTable(void) {
  struct Table *table = (struct Table *) malloc(sizeof(struct Table));
  table->head = NULL;
  return table;
}

/*
  This method initialises a table which contains the value for all the opcodes
  in an IMPS machine.
  @returns : returns a pointer to the initialised table  
*/
struct Table *initialiseOpcodeTable(void) {
  struct Table *table = initialiseEmptyTable();
  addToTable("halt",0,table);
  addToTable("add", 1,table);
  addToTable("addi",2,table);
  addToTable("sub",3,table);
  addToTable("subi",4,table);
  addToTable("mul",5,table);
  addToTable("muli",6,table);
  addToTable("lw",7,table);
  addToTable("sw",8,table);
  addToTable("beq",9,table);
  addToTable("bne",10,table);
  addToTable("blt",11,table);
  addToTable("bgt",12,table);
  addToTable("ble",13,table);
  addToTable("bge",14,table);
  addToTable("jmp",15,table);
  addToTable("jr",16,table);
  addToTable("jal",17,table);
  addToTable("out",18,table);
  return table;
}
