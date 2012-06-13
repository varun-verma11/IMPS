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

/*
  This structure defines a element in the table. Each element in the structure
  table contains a unique key and a value and pointer to the next element in the
  table.  
*/
struct Table_Elem {
  int value;
  struct Table_Elem *next;
  char *key;
};

/*
  this structure specifes the ADT table which points at the first, i.e. head of
  the table  
*/
struct Table {
  struct Table_Elem *head;
};

