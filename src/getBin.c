#include "assemble.h"

uint32_t getBin(char *tokens[5], struct Table *table, uint32_t addr){
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


