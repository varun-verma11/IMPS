#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "enum.h"

/*
  This structure stores the current assembly instruction, and the assembled 
  binary instructions in the array. It also stores the number of instructions
*/
struct Data {
  char *a_instruction;
  uint32_t b_instruction[MEMORY_SIZE];
  int number_of_instructions;
};


