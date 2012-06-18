#include "carryOutInstruction.h"

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
uint8_t getR1(uint32_t instruction){
  uint32_t mask = 0x03e00000;
  uint32_t reg = mask & instruction;
  uint8_t r1 = reg>>21;
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
  uint32_t mask = 0x0007C00;
  return ((mask & instruction) >> 11);
}/*
  This method returns the bit 16 to 31 of the given instruction
  @param instruction : this specifies the instruction
  @return            : the method returns 8 bit representation of the bit 16 to 
                       31 of the given instruction
*/
int16_t getImmediateValue(uint32_t instruction) {
  uint32_t mask = 0x0000ffff;
  return (int16_t)(mask & instruction);
}

/*
  This method returns the value stored in the specified register
  @param reg  : specifies the register index whose value has to be returned
  @param proc : specifies the processor from which the value of register has to
                be returned
  @return     : returns the value of the register specifed by the index given
*/
int32_t getRegisterValue(struct Processor *proc, int8_t reg){
  return proc->gpr[reg];
}

/*
  This method sets the value of the memory at the specified addredd to the value
  given.
  @param proc    : specifies the processor
  @param address : specifies the address of memory which needs the value to be
                   set to the given value
  @param value   : specifies the new value for the memory to be set
*/
void setMemory(struct Processor *proc, uint32_t address, int32_t value) {
  *(uint32_t *)(proc->memory + address) = value;
}

/*
  This method returns the data stored at in the memory of the specifed processor
  at the specified address.
  @param proc    : specifies the processor 
  @param address : specifies the address of the memory which data has to be
                   fetched
  @return        : returns the value stored in the memory at the specified
                   address
*/
uint32_t getMemory(struct Processor *proc, uint32_t address) {
  return *(uint32_t *)(proc->memory + address);
}

/*
  This method returns the instruction stored in the memory at address specified
  by the program counter of the processor.
  @param proc : specifies the processor which contains the program counter,
                memory, and registers
*/
uint32_t getInstructionAtPC(struct Processor *proc){
  return *(uint32_t *)(proc->memory + proc->pc);
}



int carryOutInstruction(struct Processor *processor) {
  uint32_t instruction = getInstructionAtPC(processor);
  uint8_t opcode = getOpcode(instruction);
  uint32_t backupPC = processor->pc;
  int32_t temp;
  div_t division;

  switch (opcode)  {
    case HALT : return 0;
    case ADD  : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) + 
                  getRegisterValue(processor, getR3(instruction));
                break;
                
    case ADDI : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) + 
                  getImmediateValue(instruction);
                break;
               
    case SUB  : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) - 
                  getRegisterValue(processor, getR3(instruction));
                break;
                
    case SUBI : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) - 
                   getImmediateValue(instruction);
                 break;
                  
    case MUL  : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) * 
                  getRegisterValue(processor, getR3(instruction));
                break;
                  
    case MULI : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) * 
                  getImmediateValue(instruction);
                break;
                
    case LW   : processor->gpr[getR1(instruction)] = 
                getMemory(processor, 
                          getRegisterValue(processor, getR2(instruction)) + 
                                            getImmediateValue(instruction));
                break;
                  
    case SW   : setMemory(processor, getRegisterValue
                  (processor, getR2(instruction)) + 
                  getImmediateValue(instruction), 
                  getRegisterValue(processor, getR1(instruction)));
                break;
                
    case BEQ  : if (processor->gpr[getR1(instruction)] == 
                    processor->gpr[getR2(instruction)]) 
                  { processor->pc += getImmediateValue(instruction) * 4;};
                break;
                  
      case BNE  : if (processor->gpr[getR1(instruction)] != 
                      processor->gpr[getR2(instruction)]) 
                    { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BLT  : if (processor->gpr[getR1(instruction)] <
                      processor->gpr[getR2(instruction)])
                    { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BGT  : if (processor->gpr[getR1(instruction)] >
                     processor->gpr[getR2(instruction)]) 
                   { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BLE  : if (processor->gpr[getR1(instruction)] <= 
                      processor->gpr[getR2(instruction)]) 
                  { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BGE  : if (processor->gpr[getR1(instruction)] >= 
                      processor->gpr[getR2(instruction)]) 
                    { processor->pc += (getImmediateValue(instruction) * 4);};
                  break;
                  
      case JMP  : processor->pc = getAddress(instruction);
                  break;
                  
      case JR   : processor->pc = getRegisterValue
                    (processor, getR1(instruction));
                  break;
                  
      case JAL  : processor->gpr[31] = processor->pc + sizeof(uint32_t); 
                  processor->pc = getAddress(instruction);
                  break;
                  
      case OUT  : printf("%c", (char)getRegisterValue
                    (processor, getR1(instruction)));
                  break;
                  
      case DIV  : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getRegisterValue(processor,getR3(instruction)));
                  processor->gpr[getR1(instruction)] = division.quot;
      
      case DIVI : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getImmediateValue(instruction));
                  processor->gpr[getR1(instruction)] = division.quot;
      
      case MOD  : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getRegisterValue(processor,getR3(instruction)));
                  processor->gpr[getR1(instruction)] = division.rem;
      
      case MODI : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getImmediateValue(instruction));
                  processor->gpr[getR1(instruction)] = division.rem;
      
      case FACT : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction));
                  for(int i = 1; i<processor->gpr[getR2(instruction)] ; i++) {
                    processor->gpr[getR1(instruction)] = 
                      (getRegisterValue(processor, getR1(instruction)))*
                      (getRegisterValue(processor, getR2(instruction))-i);};
                  break;
      
      case FACTI: processor->gpr[getR1(instruction)] = 
                  getImmediateValue(instruction);
                  for(int i = 1; i<getImmediateValue(instruction) ; i++) {
                    processor->gpr[getR1(instruction)] = 
                      (getRegisterValue(processor, getR1(instruction)))*
                      (getImmediateValue(instruction)-i);};
                  break;
      
      case SWAP : temp = 
                    getRegisterValue(processor, getR1(instruction));
                  processor->gpr[getR1(instruction)] = 
                    getRegisterValue(processor, getR2(instruction));
                  processor->gpr[getR2(instruction)] = temp;
                  break;
                  
      default   : printf("invalid opcode\n");
                  break;
    }
    
    if(processor->pc == backupPC)
      processor->pc += sizeof(uint32_t);
    return 0;
}
