#include "assemble.h"

uint32_t getBin(char **tokens, struct Table *table){
    char opType = getOptype(tokens[1]);
    if(opType == 'r'){
     	return parser_r(tokens, table);
    }
    else if(opType == 'i'){
    	return parser_i(tokens, table);
    }
    else if(opType == 'j'){
    	return parser_j(tokens, table);
    }
    else{
     return 0x0;
    }
}

uint32_t pass2(char *tokens[5], struct Table *table, uint32_t addr){
    if (strcmp(tokens[1],".fill")) {
      addToTable(tokens[0],atoi(tokens[2]);
      return atoi(tokens[2]);
    }
    ++tokens;
    char opType = getOptype(tokens[0]);
    if(opType == 'r'){
     	return parser_r(tokens, table);
    }
    else if(opType == 'i'){
    	return parser_i(tokens, table);
    }
    else if(opType == 'j'){
    	return parser_j(tokens, table);
    }
    else{
     return 0x0;
    }
}

int main(int argc, char **argv) {
  char instructionsTokens[][4][5] = {{"halt"},{"add","$1","$2","$3"},{"addi","$1","$2","0x99"},{"mul","$1","$2","$3"},{"jmp","0x0ff"}};
  struct Table *table = initialiseSymbolTable();
  int i = 0;
  while ( i<5) {
    printf("binary Instruction [%d] --->   0x%x \n",i, getBin(instructionsTokens[i],table));
    i++;
  }
  return EXIT_SUCCESS;
}
