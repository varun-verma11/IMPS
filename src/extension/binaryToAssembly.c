#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


 char* makeRegister(int regNum){
  char reg[4] = "$";
  char buff[2];
  itoa(regNum, buff, 10);
  strcat(reg, buff);
  return reg;

}

char* unparser_r(uint32_t binary){
 int opcode = binary>>26;
 int reg1Opcode = binary >>21;
 int reg2Opcode = binary >> 16;
 int reg3Opcode = binary >> 11;
 char* optype = getOptype(opcode);
 char reg1 = makeRegister(reg1Opcode);
 char reg2 = makeRegister(reg2Opcode);
 char reg3 = makeRegister(reg3Opcode);

 
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
char* unparser_i(uint32_t binary){
 int opcode = binary>>26;
 char* optype = getOptype(opcode);
 int reg1Opcode = binary >>21;
 int reg2Opcode = binary >> 16;
 char reg1 = makeRegister(reg1Opcode);
 char reg2 = makeRegister(reg2Opcode);

}

int main(void){
 uint32_t i;
 i  = 3;
 int j = uint32_tconverter(i);
 printf("%i\n", j);

 return EXIT_SUCCESS;

}
