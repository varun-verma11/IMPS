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

int checkLabel(char *reg){
 //if(strlen(&reg)){
  if((strcmp("a", reg)<=0 && strcmp(reg, "{")<0) || 
      (strcmp("A", reg)<=0 && strcmp("[", reg)>0)) 
  return 1;
  return 0; 
}

uint32_t parser_j(char **tokens){
 uint32_t address;
 if(checkLabel(tokens[1])){
 address = 1;
 }
 else{
 address = tokens[1];
 printf("%d \n",address);
 }
 return address;

}

int main(void){
  printf("Hi\n");
  char **tokens = malloc(100);
  tokens[0] = "add";
  tokens[1] = "0x3";
  printf("0x%x\n", parser_j(tokens));
  return EXIT_SUCCESS;
}
