#ifndef DEBUG_H
#define DEBUG_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MIN(a, b) (a > b ? b : a)

#define MEMORY_SIZE 65536
#define NUMBER_OF_REGISTERS 32
#define NUMBER_OF_COMMANDS 11
#define NUMBER_OF_INSTRUCTIONS 26
#define BUFFER_SIZE 300      
#define BREAKPOINTS_ARRAY_SIZE 100
                
char debugInstructions[][NUMBER_OF_COMMANDS] = {"list","stp","reg","mem","search","pc", "run", "q","--help","break","back","rerun"};

enum opCodes {HALT, ADD, ADDI, SUB,SUBI,MUL,MULI,LW,SW,BEQ, BNE, BLT, BGT, BLE, 
                BGE, JMP, JR, JAL, OUT, DIV, DIVI, MOD, MODI, FACT, FACTI,SWAP};

struct Processor {
  uint32_t pc;
  int32_t gpr[NUMBER_OF_REGISTERS];
  uint8_t memory[MEMORY_SIZE]; 
};

#endif
