#include "assemble.h"

int checkHex(char *reg){
  char *hex = "0x";
  char *regs = (char *) malloc(sizeof(char) *3);
  regs = strncpy(regs,reg,2);
  if(strcmp(hex , regs)==0) return 1;
  return 0;
}

uint32_t parse_fill(char **tokens, struct Table table) {
  //if : .fill operand --> that memory block is permanently assigned to operand.
  if(checkHex(tokens[2])){
    return strtol(tokens[3],NULL,16);
  } else{
    return atoi(tokens[3]);
  }
  
}

int getRegisterNumber(char *reg){
  return atoi(reg+1);
}

int checkLabel(char *reg){
  if((strcmp("a", reg)<=0 && strcmp(reg, "{")<0) || 
      (strcmp("A", reg)<=0 && strcmp("[", reg)>0)) 
  return 1;
  return 0; 
}

int checkRegister(char *token){
 return (token!=NULL) ? (token[0]=='$') : 0;
}

uint32_t parser_r(char **tokens, struct Table *table){
  uint32_t opcode = getValue(tokens[0],table)<<26;
	uint32_t reg1Opcode = (checkRegister(tokens[1])) ? getRegisterNumber(tokens[1]) <<21 : 0;
	uint32_t reg2Opcode = (checkRegister(tokens[2])) ? getRegisterNumber(tokens[2]) <<16 : 0;
	uint32_t reg3Opcode = (checkRegister(tokens[3])) ? getRegisterNumber(tokens[3]) <<11 : 0;
	return (opcode + reg1Opcode + reg2Opcode + reg3Opcode);
}

uint32_t parser_i(char **tokens,struct Table *table){
  uint32_t opcode = getValue(tokens[0],table)<<26;
  uint32_t immediateValue;
  uint32_t reg1Opcode = getRegisterNumber(tokens[1])<<21;
  uint32_t reg2Opcode = getRegisterNumber(tokens[2])<<16;

  if(checkHex(tokens[3])){
    immediateValue = (int) strtol(tokens[3],NULL,16);
  } else if(checkLabel(tokens[3])) {
    immediateValue = (int) getValue(tokens[3], table);
  }else{
    immediateValue = atoi(tokens[3]);
  }
  return (opcode + reg1Opcode + reg2Opcode + immediateValue);
}

uint32_t parser_j(char **tokens, struct Table *table){
  uint32_t address;
  uint32_t opcode = getValue(tokens[0],table)<<26;
  if(checkLabel(tokens[1])){
    address = getValue(tokens[1],table);
  } else {
    address = *tokens[1];
  }
  return address+opcode;
}

