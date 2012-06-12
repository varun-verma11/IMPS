#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MIN(a, b) (a > b ? b : a)
#define MEMORY_SIZE 65536
#define NUMBER_OF_REGISTERS 32
#define NUMBER_OF_COMMANDS 7

/*
  The enumeration opCodes stores all the opcodes which a user can have in the 
  file
*/
enum opCodes {HALT, ADD, ADDI, SUB,SUBI,MUL,MULI,LW,SW,BEQ, BNE, BLT, BGT, BLE, 
                BGE, JMP, JR, JAL, OUT};
                
char debugInstructions[][NUMBER_OF_COMMANDS] = {"cur","stp","reg","mem","search","pc", "run"};
