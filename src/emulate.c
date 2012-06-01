#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#define MEMORY_SIZE 65536

/*
  The enumeration opCodes stores all the opcodes which a user can have in the 
  file
*/
enum opCodes {HALT, ADD, ADDI, SUB,SUBI,MUL,MULI,LW,SW,BEQ, BNE, BLT, BGT, BLE, 
                BGE, JMP, JR, JAL, OUT};

/*
  The structure processor stores the state of the processor. pc is used to store
  the value of program counter; gpr are the 32-bit general purpose registers;
  and the array memory represents the memory of the memory size specified.
*/
struct Processor {
  uint32_t pc;
  uint32_t gpr[32];
  uint32_t memory[MEMORY_SIZE]; 
};

/*
  The method binaryFileLoader loads the binary file in the memory of the given
  processor.
  @param processor : this specifes the current processor with the memory to be
                     initialised with the given instructions from given filepath
  @param filepath  : this specifies the path of the file which contains the
                     instructions to be loaded in the memory.
*/
void binaryFileLoader(char *filepath, struct Processor *processor) {
  FILE *fp;
  (fp = fopen(filepath,"rb"));
  if (fp==NULL) {
    perror("ERROR in opening file");
    exit(EXIT_FAILURE);
  }
  fread(&(processor->memory), 32, MEMORY_SIZE, fp);
  fclose(fp);
}

/*
  This method returns the opcode (bit 0 to 5) from the given 32 bit instruction
  @param instruction : This specifies the 32 bit instruction
  @return            : The method returns 8bit representation of the opcode
*/
uint8_t getOpcode(uint32_t instruction) {
  uint32_t mask = 0xfc000000;
  uint32_t opcd = mask & instruction;
  opcd = opcd >> 26;
  uint8_t opCode = (int) opcd;
  return opCode;
}


/*
  This method returns the bit 6 to 31 of the given instruction, i.e. the address
  for j-type instructions
  @param instruction : this specifies the instruction
  @return            : the method returns 32 bit representation of the bit 6 to 
                       31 of the given instruction
*/
uint32_t getAddress(uint32_t instruction) {
  uint32_t mask = 0x03ffffff;
  return mask & instruction;
}

/*
  This method returns the bit 6 to 10 of the given instruction
  @param instruction : this specifies the instruction
  @return            : the method returns 8 bit representation of the bit 6 to 
                       10 of the given instruction
*/
uint8_t getR1(uint32_t instruction) {
  uint32_t mask = 0x03e00000;
  uint32_t reg = mask & instruction;
  uint8_t r1 = reg >> 21;
  return r1;
}

/*
  This method returns the bit 11 to 15 of the given instruction
  @param instruction : this specifies the instruction
  @return            : the method returns 8 bit representation of the bit 11 to 
                       15 of the given instruction
*/
uint8_t getR2(uint32_t instruction) {
  uint32_t mask = 0x001f0000;
  uint32_t reg = mask & instruction;
  uint8_t r2 = reg >> 16;
  return r2;
}

/*
  This method returns the bit 16 to 21 of the given instruction
  @param instruction : this specifies the instruction
  @return            : the method returns 8 bit representation of the bit 16 to 
                       21 of the given instruction
*/
uint8_t getR3(uint32_t instruction) {
  uint32_t mask = 0x000f8000;
  return ((mask & instruction) >> 15);
}

/*
  This method returns the bit 16 to 31 of the given instruction
  @param instruction : this specifies the instruction
  @return            : the method returns 8 bit representation of the bit 16 to 
                       31 of the given instruction
*/
uint16_t getImmediateValue(uint32_t instruction) {
  uint32_t mask = 0x0000ffff;
  return (mask & instruction);
}

/*
  This method returns a new value for the pc to pc
  @param instruction : this specifies the instruction
  @return            : the method returns 8 bit representation of the bit 6 to 
                       10 of the given instruction
*/
uint32_t setPC(uint32_t instruction,uint32_t pc) {
  pc--;
  return pc+(getImmediateValue(instruction)*4);
}

/*
void setPC(struct Processor *processor) {
  --(&(processor->pc));
  (&(processor->pc)) = (&(processor->pc)) + (getImmediateValue(processor->memory[(&(processor->pc))])*4);
}
*/

/*
  This method 
  @param argv : this specifies the argueents which were given through the
                terminal when the program was run.
  @param argc : this specifes the number of arguments provided
  @return     : the method returns 0 when the method executes without any errors
*/
int main(int argc, char **argv) {
  assert("There are wrong number of arguents given" && argc==2);
  struct Processor processor;
  processor.pc = 0;
  char *filepath = argv[1];
  printf("%s\n",filepath);
  binaryFileLoader(filepath, &processor);
    
  while (1) {
    uint32_t instruction = processor.memory[(int) processor.pc];
    uint8_t opcode = getOpcode(processor.memory[processor.pc]);
    ++processor.pc;
    switch (opcode) {
      case HALT : return EXIT_SUCCESS;
      case ADD  : processor.gpr[getR1(instruction)] = processor.gpr[getR2(instruction)] + processor.gpr[getR3(instruction)] ; break;
      case ADDI : processor.gpr[getR1(instruction)] = processor.gpr[getR2(instruction)] + 
                    getImmediateValue(instruction) ; break;
      case SUB  : processor.gpr[getR1(instruction)] = processor.gpr[getR2(instruction)] - processor.gpr[getR3(instruction)] ; break;
      case SUBI : processor.gpr[getR1(instruction)] = processor.gpr[getR2(instruction)] - 
                    getImmediateValue(instruction) ; break;
      case MUL  : processor.gpr[getR1(instruction)] = processor.gpr[getR2(instruction)] * processor.gpr[getR3(instruction)] ; break;
      case MULI : processor.gpr[getR1(instruction)] = processor.gpr[getR2(instruction)] * 
                    getImmediateValue(instruction) ; break;
      case LW   : processor.gpr[getR1(instruction)] = processor.memory[getR2(instruction) + getImmediateValue(instruction)];
      case SW   : processor.memory[getR2(instruction) + getImmediateValue(instruction)] = processor.gpr[getR1(instruction)];
      case BEQ  : if (&(processor.gpr[getR1(instruction)])==&(processor.gpr[getR1(instruction)])) { setPC(instruction, processor.pc);};
      case BNE  : if (&(processor.gpr[getR1(instruction)])!=&(processor.gpr[getR1(instruction)])) { setPC(instruction,processor.pc);};
      case BLT  : if (&(processor.gpr[getR1(instruction)])<&(processor.gpr[getR1(instruction)]))  { setPC(instruction,processor.pc);};
      case BGT  : if (&(processor.gpr[getR1(instruction)])>&(processor.gpr[getR1(instruction)]))  { setPC(instruction,processor.pc);};
      case BLE  : if (&(processor.gpr[getR1(instruction)])<=&(processor.gpr[getR1(instruction)])) { setPC(instruction,processor.pc);};
      case BGE  : if (&(processor.gpr[getR1(instruction)])>=&(processor.gpr[getR1(instruction)])) { setPC(instruction,processor.pc);};
      case JMP  : processor.pc = getAddress(instruction);
      case JR   : processor.pc = (getR1(instruction));
      case JAL  : processor.gpr[31] = processor.pc + 4; processor.pc = getAddress(instruction);
      case OUT  : printf("%c\n",processor.gpr[getR1(instruction)]);
    }
  }

  return EXIT_SUCCESS;
}
