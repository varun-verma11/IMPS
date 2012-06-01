#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MEMORY_SIZE 65536
#define NUMBER_OF_REGISTERS 32

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
  int32_t gpr[NUMBER_OF_REGISTERS];
  uint8_t memory[MEMORY_SIZE]; 
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
  fp = fopen(filepath,"rb");
  if (fp==NULL) {
    perror("ERROR in opening file");
    exit(EXIT_FAILURE);
  }

  int fileSize;
  
  fseek (fp , 0 , SEEK_END);
  fileSize = ftell (fp);
  rewind (fp);

  // fileSize = MIN(65536, fileSize);

  fread(processor->memory, sizeof(uint32_t), fileSize, fp);
  /*
  int i = sizeof(fp);
  while ( i!=0) {
    printf("%d\t",i);
    printf("%x\n",(processor->memory[i]));
    i--;
  }
  */
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
  uint32_t mask = 0xf8000;
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
  uint32_t mask = 0x00073000;
  return ((mask & instruction) >> 11);
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

void setMemory(struct Processor *proc, uint32_t address, int32_t value)
{
  *(uint32_t *)(proc->memory + address) = value;
}

uint32_t getMemory(struct Processor *proc, uint32_t address)
{
  return *(uint32_t *)(proc->memory + address);
}

uint32_t getInstructionAtPC(struct Processor *proc)
{
  return *(uint32_t *)(proc->memory + proc->pc);
}

int32_t getRegisterValue(struct Processor *proc, int8_t reg)
{
  return proc->gpr[reg];
}

/*
void setPC(struct Processor *processor) {
  --(&(processor->pc));
  (&(processor->pc)) = (&(processor->pc)) + (getImmediateValue(processor->memory[(&(processor->pc))])*4);
}
*/

/**

      case LW   : processor.gpr[getR1(instruction)] = processor.memory[getRegisterValue(&processor, getR2(instruction)) + getRegisterValue(&processor, getImmediateValue(instruction))];
        break;
      case SW   : processor.memory[getRegisterValue(&processor, getR2(instruction)) + getRegisterValue(&processor, getImmediateValue(instruction))] = getRegisterValue(&processor, getR1(instruction));
        break;
        
**/

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
  char *filepath = argv[1];

  memset(&processor, 0, sizeof(struct Processor));

  binaryFileLoader(filepath, &processor);
    
  while (1) {
    uint32_t instruction = getInstructionAtPC(&processor);
    uint8_t opcode = getOpcode(instruction);
    processor.pc += sizeof(uint32_t);
    switch (opcode) {
      case HALT : return EXIT_SUCCESS;
      case ADD  : processor.gpr[getR1(instruction)] = getRegisterValue(&processor, getR2(instruction)) + getRegisterValue(&processor, getR3(instruction));
        break;
      case ADDI : processor.gpr[getR1(instruction)] = getRegisterValue(&processor, getR2(instruction)) + getImmediateValue(instruction);
        break;
      case SUB  : processor.gpr[getR1(instruction)] = getRegisterValue(&processor, getR2(instruction)) - getRegisterValue(&processor, getR3(instruction));
        break;
      case SUBI : processor.gpr[getR1(instruction)] = getRegisterValue(&processor, getR2(instruction)) - getImmediateValue(instruction);
        break;
      case MUL  : processor.gpr[getR1(instruction)] = getRegisterValue(&processor, getR2(instruction)) * getRegisterValue(&processor, getR3(instruction));
        break;
      case MULI : processor.gpr[getR1(instruction)] = getRegisterValue(&processor, getR2(instruction)) * getImmediateValue(instruction);
        break;
      case LW   : processor.gpr[getR1(instruction)] = getMemory(&processor, getR2(instruction) + getImmediateValue(instruction));
        break;
      case SW   : setMemory(&processor, getRegisterValue(&processor, getR2(instruction)) + getImmediateValue(instruction), getRegisterValue(&processor, getR1(instruction)));
        break;
      case BEQ  : if (processor.gpr[getR1(instruction)] == processor.gpr[getR2(instruction)]) { processor.pc += getImmediateValue(instruction) * 4;};
        break;
      case BNE  : if (processor.gpr[getR1(instruction)] != processor.gpr[getR2(instruction)]) { processor.pc += getImmediateValue(instruction) * 4;};
        break;
      case BLT  : if (processor.gpr[getR1(instruction)] < processor.gpr[getR2(instruction)]) { processor.pc += getImmediateValue(instruction) * 4;};
        break;
      case BGT  : if (processor.gpr[getR1(instruction)] > processor.gpr[getR2(instruction)]) { processor.pc += getImmediateValue(instruction) * 4;};
        break;
      case BLE  : if (processor.gpr[getR1(instruction)] <= processor.gpr[getR2(instruction)]) { processor.pc += getImmediateValue(instruction) * 4;};
        break;
      case BGE  : if (processor.gpr[getR1(instruction)] >= processor.gpr[getR2(instruction)]) { processor.pc += getImmediateValue(instruction) * 4;};
        break;
      case JMP  : processor.pc = getAddress(instruction);
        break;
      case JR   : processor.pc = getRegisterValue(&processor, getR1(instruction));
        break;
      case JAL  : processor.gpr[31] = processor.pc + 4; processor.pc = getAddress(instruction);
        break;
      case OUT  : printf("%c\n", (char)getRegisterValue(&processor, getR1(instruction)));
      /*
        {
          uint32_t reg = getR1(instruction);
          printf("out instruction: %d -> 0x%08X\n", reg, processor.gpr[reg]);
          // printf("%c", (char)getRegisterValue(&processor, getR1(instruction)));
        }
        */
        break;
      default : printf("invalid opcode\n");
        break;
    }
  }

  return EXIT_SUCCESS;
}
