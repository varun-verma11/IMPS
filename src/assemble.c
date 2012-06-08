#include "assemble.h"

char getOptype(char *opcode) {
  if (strcmp("halt", opcode)==0) {
    return '-';
  } else if (strcmp("add", opcode)==0) {
    return 'r';
  } else if (strcmp("addi", opcode)==0) {
    return 'i';
  } else if (strcmp("sub", opcode)==0) {
    return 'r';
  } else if (strcmp("subi", opcode)==0) {
    return 'i';
  } else if (strcmp("mul", opcode)==0) {
    return 'r';
  } else if (strcmp("muli", opcode)==0) {
    return 'i';
  } else if (strcmp("lw", opcode)==0) {
    return 'i';
  } else if (strcmp("sw", opcode)==0) {
    return 'i';
  } else if (strcmp("beq", opcode)==0) {
    return 'i';
  } else if (strcmp("bne", opcode)==0) {
    return 'i';
  } else if (strcmp("blt", opcode)==0) {
    return 'i';
  } else if (strcmp("bgt", opcode)==0) {
    return 'i';
  } else if (strcmp("ble", opcode)==0) {
    return 'i';
  } else if (strcmp("bge", opcode)==0) {
    return 'i';
  } else if (strcmp("jmp", opcode)==0) {
    return 'j';
  } else if (strcmp("jr", opcode)==0) {
    return 'r';
  } else if (strcmp("jal", opcode)==0) {
    return 'j';
  } else if (strcmp("out", opcode)==0) {
    return 'r';
  } else {
    return 'e';
  }  
}

void readFromFile(char *filepath, struct Data *data) {
  FILE *fp;
  fp = fopen(filepath, "wb");
  if (fp==NULL) {
    perror("Error is writing to file");
    exit(EXIT_FAILURE);
  }
  data->a_instructions = malloc(sizeof(fp) * sizeof(char));
  char buffer[BUFFER_SIZE];
  int i=0;
  while((feof(fp)==0) && (i<=MEMORY_SIZE)) {
    fgets(buffer,sizeof(buffer), stdin);
    data->a_instructions[i] = buffer;
    memset(&buffer,' ' , sizeof(buffer));
    i++;    
  }
  fclose(fp); 
}

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

void writeToFile(char *filepath, struct Data *data) { 
  FILE *fp;
  fp = fopen(filepath, "wb");
  /*check if needed*/
  if (fp==NULL) {
    perror("Error is writing to file");
    exit(EXIT_FAILURE);
  }
	int num_of_elem_written = 0;
  int num_of_elem = data->number_of_instructions;
	num_of_elem_written = fwrite((data->b_instructions),sizeof(uint32_t), num_of_elem, fp);
	
	if (num_of_elem_written != num_of_elem) {
		perror("ERROR IN WRITING TO FILE");
		exit(EXIT_FAILURE);
 	}
  fclose(fp);
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
