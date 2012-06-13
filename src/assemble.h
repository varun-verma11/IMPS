#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

/*
  This structure stores the current assembly instruction, and the assembled 
  binary instructions in the array. It also stores the number of instructions
*/
struct Data {
  char *a_instruction;
  uint32_t b_instruction[MEMORY_SIZE];
  int number_of_instructions;
};

/*
  This enum specifies the opcodes which can be given in the file
*/
enum opCodes {HALT=0, ADD, ADDI, SUB, SUBI, MUL, MULI, LW, SW, BEQ, BNE, BLT, BGT, BLE, 
                BGE, JMP, JR, JAL, OUT};

