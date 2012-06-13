#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

struct Data {
  char *a_instruction;
  uint32_t b_instruction;
  int number_of_instructions;
};

enum opCodes {HALT=0, ADD, ADDI, SUB, SUBI, MUL, MULI, LW, SW, BEQ, BNE, BLT, BGT, BLE, 
                BGE, JMP, JR, JAL, OUT};

struct Table_Elem {
  int value;
  struct Table_Elem *next;
  char *key;
};

struct Table {
  struct Table_Elem *head;
};
