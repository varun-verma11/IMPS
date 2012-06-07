#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct Table_Elem {
  int value;
  struct Table_Elem *next;
  char *key;
};

struct Table {
  struct Table_Elem *head;
};

uint32_t convertedOpcode=0;





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
    printf("%d\n", current->value);
    if (strcmp(key,current->key)==0) return current->value;
    current = current->next;
  }
  return -1;
}

struct Table *initialiseSymbolTable(void) {
  struct Table *t= malloc(sizeof(struct Table));
  t->head = NULL;

  addToTable("add",1,t);
    addToTable("halt",0,t);
  return t;
}
















// fails. checks if the whole reg (eg "$4") == "$"

int getRegisterNumber(char *reg){
  char *regNumber = malloc(sizeof(char) *2);

  for(int i = 0; ; i++){
     if(i == strlen(reg)) break;
     regNumber[i] = reg[i+1];
  }
  return atoi(regNumber);

}

int checkHex(char *reg){
  char *hex = "0x";
  char *regs = (char *) malloc(sizeof(char) *3);
  regs = strncpy(regs,reg,2);
  if(strcmp(hex , regs)==0) return 1;
  return 0;
}


int checkLabel(char *reg){
 //if(strlen(&reg)){
  if((strcmp("a", reg)<=0 && strcmp(reg, "{")<0) || 
      (strcmp("A", reg)<=0 && strcmp("[", reg)>0)) 
  return 1;
  return 0; 
}


/*
int convertOpcode(char *tokens){
  int convertedOpcode = (int) getValue(tokens[0]);
  return convertedOpcode;
}
*/

uint32_t parser_r(char **tokens){
   //2 registers saved into a given register
   uint32_t opcode = getValue(tokens[0]);;
   uint32_t reg1Opcode = getRegisterNumber(tokens[1]) <<21;
   uint32_t reg2Opcode = getRegisterNumber(tokens[2])<<16;
   uint32_t reg3Opcode = getRegisterNumber(tokens[3])<<11;
   return (opcode + reg1Opcode + reg2Opcode + reg3Opcode); 
}


uint32_t parser_i(char **tokens, struct Table *table){
   uint32_t immediateValue;
   int reg1 = getRegisterNumber(tokens[1]);
   int reg2 = getRegisterNumber(tokens[2]);
   uint32_t reg1Opcode = reg1<<21;
   uint32_t reg2Opcode = reg2<<16;
   
   if(checkHex(tokens[3])){
    immediateValue = (uint32_t) *tokens[3];
   } else if(checkLabel(tokens[3])){
    immediateValue = (int) getValue(tokens[3], table);
   }else{
    immediateValue = (int) *tokens[3];
   }
   return (reg1Opcode + reg2Opcode + immediateValue);

}

uint32_t parser_j(char **tokens, struct Table *table){
 uint32_t address;
 if(checkLabel(tokens[1])){
 address = (int) getValue(tokens[1], table);
 }
 else{
 address = (uint32_t) tokens[1];
 }
 return address;

}



int main(void){
  printf("Hi\n");
  struct Table *table = initialiseSymbolTable();
  printf("%d\n",getValue("add",table));

  char **tokens ={"add","$1","$2","$3"};
  printf("jose");
  uint32_t ins = parser_r(tokens);

  printf("%d\n",ins);
  return EXIT_SUCCESS;
}

 






