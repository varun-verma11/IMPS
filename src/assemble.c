#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

struct Data {
  char **a_instructions;
  uint32_t b_instructions[MEMORY_SIZE];
	int number_of_instructions;
};

enum opCodes {HALT=0, ADD, ADDI, SUB, SUBI, MUL, MULI, LW, SW, BEQ, BNE, BLT, BGT, BLE, 
                BGE, JMP, JR, JAL, OUT};

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



int main(int argc, char **argv) {
  struct Data data;
  return EXIT_SUCCESS;
}
