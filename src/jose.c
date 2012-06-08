#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


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

uint32_t parser_i(char **tokens,struct Table table){
  uint32_t opcode = getValue(token[0],table)<<26;
  uint32_t immediateValue;
  uint32_t reg1Opcode = getRegisterNumber(tokens[1])<<21;
  uint32_t reg2Opcode = getRegisterNumber(tokens[2])<<16;

  if(checkHex(tokens[3])){
    immediateValue = (int) strtol(tokens[3],NULL,16);
  } else if(checkLabel(tokens[3])){
    immediateValue = (int) getValue(tokens[3], table);
  }else{
    immediateValue = atoi(tokens[3]);
  }
  return (opcode + reg1Opcode + reg2Opcode + immediateValue);
}

uint32_t parser_j(char **tokens, struct Table *table){
  uint32_t address;
  uint32_t opcode = getValue(token[0],table)<<26;
  if(checkLabel(tokens[1])){
    address = getValue(token[1],table);
  } else {
    address = *tokens[1];
  }
  return address+opcode;
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

 






