#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
struct Data{
};


uint32_t convertedOpcode=0;

uint32_t make_it(char **tokens, struct Data *data){
uint32_t opcode = (int) getValue(tokens[0]);
return opcode;
/* convertOpcode(tokens[0])<<26;*/

}
/*
int convertOpcode(char *tokens){
  int convertedOpcode = (int) getValue(tokens[0]);
  return convertedOpcode;
}
*/
uint32_t parser_r(char **tokens){
 //2 registers saved into a given register
 int reg1 = (int) getRegisterNumber(tokens[1]);
 int reg2 = (int) getRegisterNumber(tokens[2]);
 int reg3 = (int) getRegisterNumber(tokens[3]);
 uint32_t reg1Opcode = reg1<<21;
 uint32_t reg2Opcode = reg2<<16;
 uint32_t reg3Opcode = reg3<<11;
 return (reg1Opcode + reg2Opcode + reg3Opcode); 
}

uint32_t parser_j(char **tokens){
 int reg1 = (int) getRegisterNumber(tokens[1]);
 int reg2 = (int) getRegisterNumber(tokens[2]);
 uint32_t reg1Opcode = reg1<<21;
 uint32_t reg2Opcode = reg2<<16;
 if(checkhex(tokens[3])){
  uint32_t immediateValue = (uint32_t) tokens[3];
 } else if(checkLabel(tokens[3])){
  uint32_t immediateValue = (int) getValue(tokens[3]);
 }else{
  uint32_t immediateValue = (int) tokens[3];
 }
 return (reg1Opcode + reg2Opcode + immediateValue);

}

uint32_t parser_i(char **tokens){
 if(checkLabel(tokens[1])){
 uint32_t address = (int) getValue(tokens[1]);
 }
 else{
 uint32_t address = (uint32_t) tokens[1]
 }
 return address;

}

char *getRegisterNumber(char *reg){
 if(strcmp("$", &reg1)==0){
   char *regNumber[strlen(*reg) -2];
   for(int i = 0; i<strlen(&reg)-1; i++){
     &regNumber[i] = &reg[i+1];
   }
  return regNumber;
 }
}
int checkHex(char *reg){
 if(reg[0]==0 &&reg[1] == 'x'){
  return 0;
 }
 else{
 return 1;
 }

}
int checkLabel(char *reg){
 
}
 

int main(){
return 0;
}
void getValue(char *tokens){
}
 
}





