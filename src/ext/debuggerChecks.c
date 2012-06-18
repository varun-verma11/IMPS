#include "debuggerChecks.h"

/*
  This method checks if the given tokenn is a register or not.
  @param token : specifes the token to be checked
  @return      : returns 1 if the given token is a register
*/
int checkRegister(char *token){
 return (token!=NULL) ? (token[0]=='$') : 0;
}

/*
  This method returns an integer value for the given register
  @param reg : specifes the reg whose int value has to be returned
  @return    : returns integer representation of the given string value 
               representation of the token
*/
int getRegisterNumber(char *reg){
  return atoi(reg+1);
}



int checkIfNumber(char *num) {
  char *temp = num;
  while(*temp) {
    if (!isdigit(*temp)) return 0;
    temp++;
  }
  return 1;
}

int checkAllRegistersAreValid(char **regs) {
  while (*regs) {
    if (!checkRegister(*regs) || !checkIfNumber(*regs+1) || 
              getRegisterNumber(*regs) <0 || 
              getRegisterNumber(*regs) >= NUMBER_OF_REGISTERS) {
      return 0;
    }
    regs++;
  }
  return 1;
}

int checkIfAllMemoryLocationsAreValid(char **tokens) {
  while(*tokens) {
    if (!checkIfNumber(*tokens) || atoi(*tokens) <0 
                || atoi(*tokens)>=MEMORY_SIZE) return 0;
    tokens++;
  }
  return 1;
}


int checkIfBreakPoint(int *breakPoints, int lineNumber) {
  for (int i=0; i<BREAKPOINTS_ARRAY_SIZE ;i++) {
    if (breakPoints[i]==lineNumber) return 1;
    if (breakPoints[i]==-1) return 0;
    i++;
  }
  return 0;
}

int checkRtypeInstructionIsValid(uint32_t ins) {
  uint8_t r1 = getR1(ins);
  uint8_t r2 = getR2(ins);
  uint8_t r3 = getR3(ins);
  if (r1<0 || r2<0 || r3<0 || r1>=NUMBER_OF_REGISTERS || r2>=NUMBER_OF_REGISTERS 
        || r3>=NUMBER_OF_REGISTERS) {
    printSegmentationFaultMessage();
    return 0;
  }
  return 1;
}

int checkBrachInstructionIsValid(uint32_t ins, struct Processor *proc) {
  uint8_t r1 = getR1(ins);
  uint8_t r2 = getR2(ins);
  int16_t iVal = getImmediateValue(ins);
  uint32_t pc = proc->pc;
  if (r1<0 || r2<0 || r1>=NUMBER_OF_REGISTERS || r2>=NUMBER_OF_REGISTERS 
                                || pc+(iVal*4)<0 || pc+(iVal*4)>=MEMORY_SIZE) {
    printSegmentationFaultMessage();
    return 0;
  }
  return 1;
}

int checkItypeInstructionIsValid(uint32_t ins) {
  uint8_t r1 = getR1(ins);
  uint8_t r2 = getR2(ins);
  if (r1<0 || r2<0 || r1>=NUMBER_OF_REGISTERS || r2>=NUMBER_OF_REGISTERS) {
    printSegmentationFaultMessage();
    return 0;
  }
  return 1;
}

int checkJtypeIsValid(uint32_t ins) {
  uint32_t add = getAddress(ins);
  if (add<0 || add>=MEMORY_SIZE) {
    printSegmentationFaultMessage();
    return 0;
  }
  return 1;
}

int checkIfLoadAndStoreAreValid(uint32_t ins) {
  uint8_t r1 = getR1(ins);
  uint8_t r2 = getR2(ins);
  int16_t iVal = getImmediateValue(ins);
  if (r1<0 || r2<0 || r1>=NUMBER_OF_REGISTERS || r2>=NUMBER_OF_REGISTERS 
                                        || r2+iVal<0 || r2+iVal>=MEMORY_SIZE) {
    printSegmentationFaultMessage();
    return 0;
  }
  return 1;
}

int checkIfInstructionIsValid(struct Processor *processor) {
  uint32_t instruction = getInstructionAtPC(processor);
  uint8_t opcode = getOpcode(instruction);
  if (opcode<0 || opcode>NUMBER_OF_INSTRUCTIONS) {
    printf("The opcode for the current instruction is invalid. This would cause SEGMENTATION FAULT\n");
    programExitValue =1;
    return 0;    
  };
  switch (opcode)  {
    case HALT : return 1;
    case ADD  : return checkRtypeInstructionIsValid(instruction)!=0;
    case ADDI :return checkItypeInstructionIsValid(instruction)!=0;
    case SUB  : return checkRtypeInstructionIsValid(instruction)!=0;
    case SUBI : return checkItypeInstructionIsValid(instruction)!=0;
    case MUL  : return checkRtypeInstructionIsValid(instruction)!=0;
    case MULI : return checkItypeInstructionIsValid(instruction)!=0;
    case LW   : return checkIfLoadAndStoreAreValid(instruction)!=0; 
    case SW   : return checkIfLoadAndStoreAreValid(instruction)!=0;
    case BEQ  : return checkBrachInstructionIsValid(instruction,processor)!=0;
    case BNE  : return checkBrachInstructionIsValid(instruction,processor)!=0; 
    case BLT  : return checkBrachInstructionIsValid(instruction,processor)!=0;
    case BGT  : return checkBrachInstructionIsValid(instruction,processor)!=0;
    case BLE  : return checkBrachInstructionIsValid(instruction,processor)!=0;
    case BGE  : return checkBrachInstructionIsValid(instruction,processor)!=0;
    case JMP  : return checkJtypeIsValid(instruction)!=0;
    case JR   : return checkRtypeInstructionIsValid(instruction)!=0;
    case JAL  : return checkJtypeIsValid(instruction)!=0;
    case OUT  : return checkRtypeInstructionIsValid(instruction)!=0;
    case DIV  : return checkRtypeInstructionIsValid(instruction)!=0;
    case DIVI : return checkItypeInstructionIsValid(instruction)!=0;
    case MOD  : return checkRtypeInstructionIsValid(instruction)!=0;
    case MODI : return checkItypeInstructionIsValid(instruction)!=0;
    case FACT : return checkRtypeInstructionIsValid(instruction)!=0;
    case FACTI: return checkItypeInstructionIsValid(instruction)!=0;
    case SWAP : return checkRtypeInstructionIsValid(instruction)!=0;
    default   : return 0;
  }
}
