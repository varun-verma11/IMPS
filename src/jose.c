#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>



uint32_t convertedOpcode=0;


void* getValue(char **tokens){
}

char *getRegisterNumber(char *reg){
// char *regNumber[strlen(reg) -2];
char *regNumber;
 if(strcmp("$", reg)==0){
   for(int i = 0; i<strlen(reg)-1; i++){
     regNumber[i] = reg[i+1];
   }
  return regNumber;
 }
}


int checkHex(char *reg){
 if(reg[0]==0 && reg[1] == 'x'){
  return 1;
 }
 else{
 return 0;
 }

}

int checkLabel(char *reg){
 if(strlen(reg)){
 return 0;
 }
}


uint32_t make_it(char **tokens){
uint32_t opcode = (int) getValue(&tokens[0]);
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
 int reg1 = (int) *getRegisterNumber(tokens[1]);
 int reg2 = (int) *getRegisterNumber(tokens[2]);
 int reg3 = (int) *getRegisterNumber(tokens[3]);
 uint32_t reg1Opcode = reg1<<21;
 uint32_t reg2Opcode = reg2<<16;
 uint32_t reg3Opcode = reg3<<11;
 return (reg1Opcode + reg2Opcode + reg3Opcode); 
}

uint32_t parser_j(char **tokens){
 uint32_t immediateValue;
 int reg1 = (int) *getRegisterNumber(tokens[1]);
 int reg2 = (int) *getRegisterNumber(tokens[2]);
 uint32_t reg1Opcode = reg1<<21;
 uint32_t reg2Opcode = reg2<<16;
 if(checkHex(tokens[3])){
  immediateValue = (uint32_t) *tokens[3];
 } else if(checkLabel(tokens[3])){
  immediateValue = (int) getValuetokens[3]);
 }else{
  immediateValue = (int) *tokens[3];
 }
 return (reg1Opcode + reg2Opcode + immediateValue);

}

uint32_t parser_i(char **tokens){
 uint32_t address;
 if(checkLabel(tokens[1])){
 address = (int) getValue(tokens[1]);
 }
 else{
 address = (uint32_t) tokens[1];
 }
 return address;

}



int main(void){
printf("Hi");
char **tokens = {"add","$1","$2","$3"};
uint32_t ins = parser_r(tokens);

printf("%d\n",ins);
return EXIT_SUCCESS;
}

 






