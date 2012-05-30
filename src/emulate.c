#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#define MEMORY_SIZE 65536

enum opCodes {HALT=0, ADD, ADDI, SUB,SUBI,MUL,MULI,LW,SW,BEQ, BNE, BLT, BGT, BLE, 
                BGE, JMP, JR, JAL, OUT};

struct Processor {
  uint32_t pc;
  uint32_t gpr[32];
  uint32_t memory[MEMORY_SIZE]; 
};

void binaryFileLoader(char filepath[], struct Processor processor) {
  FILE *fp;
  if ((fp = fopen(filepath,"b")==NULL)) {
    perror("ERROR in opening file");
    exit(EXIT_FAILURE);
  }
  fread(&(processor->memory), 32, MEMORY_SIZE, fp);
  fclose(fp);
}

uint8_t getOpcode(uint32_t instruction) {
  uint32_t mask = 0xfc000000;
  uint32_t opcd = mask & instruction;
  opcd = opcd >> 26;
  uint8_t opCode = opcd;
  return opCode;
}
/*
The method below will get the opType from a given instruction as a char
of the corresponding type. This is used by the method parseInstruction which
reads the binary instruction and sets the value of registers, addresses and/or
Immediate values accordingly.

-Ganesh
*/
char getOptype(uint32_t instruction) {
  char opType;
  switch (getOpcode(instruction)) {
    case ADD  : opType = 'r'; break;
    case ADDI : opType = 'i'; break;
    case SUB  : opType = 'r'; break;
    case SUBI : opType = 'i'; break;
    case MUL  : opType = 'r'; break;
    case MULI : opType = 'i'; break;
    case LW   : opType = 'i'; break;
    case SW   : opType = 'i'; break;
    case BEQ  : opType = 'i'; break;
    case BNE  : opType = 'i'; break;
    case BLT  : opType = 'i'; break;
    case BGT  : opType = 'i'; break;
    case BLE  : opType = 'i'; break;
    case BGE  : opType = 'i'; break;
    case JMP  : opType = 'i'; break;
    case JR   : opType = 'r'; break;
    case JAL  : opType = 'j'; break;
    case OUT  : opType = 'r'; break;
    default   : opType = opType;
  }
  return opType;
}

void parseInstruction(uint32_t instruction) {
  uint32_t mask1;
  uint32_t mask2;
  uint32_t mask3;
  if(getOptype(instruction)=='i') {
    mask1 = 0x03e00000;
    mask2 = 0x001f0000;
    mask3 = 0x0000ffff;
  }
  if(getOptype(instruction)=='r') {
    mask1 = 0x03e00000;
    mask2 = 0x001f0000;
    mask3 = 0x000f8000;
  }
  if(getOptype(instruction)=='j') {
    mask1 = 0x03ffffff;
  }
}

int main(int argc, char **argv) {
  assert("There are wrong number of arguents given" && argc==1);
  struct Processor processor;
  processor.pc = 0;
  char filepath[] = argv[0];
  binaryFileLoader(filepath, processor);
    
  while (true) {
    uint8_t opcode = getOpcode(processor.memory[processor.pc]);
    ++processor.pc;
    switch (opcode) {
      case HALT : return EXIT_SUCCESS;
      case ADD  : processor.gpr[] = processor.gpr[] + processor.gpr[] ; break;
      case ADDI : processor.gpr[] = processor.gpr[] + 
                    getImmediateValue(processor.memory[processor.pc]) ; break;
      case SUB  : processor.gpr[] = processor.gpr[] - processor.gpr[] ; break;
      case SUBI : processor.gpr[] = processor.gpr[] - 
                    getImmediateValue(processor.memory[processor.pc]) ; break;
      case MUL  : processor.gpr[] = processor.gpr[] * processor.gpr[] ; break;
      case MULI : processor.gpr[] = processor.gpr[] * 
                    getImmediateValue(processor.memory[processor.pc]) ; break;
      case LW   :
      case SW   :
      case BEQ  :
      case BNE  :
      case BLT  :
      case BGT  :
      case BLE  :
      case BGE  :
      case JMP  :
      case JR   :
      case JAL  :
      case OUT  :
    }
  }
  
  return EXIT_SUCCESS;
}
