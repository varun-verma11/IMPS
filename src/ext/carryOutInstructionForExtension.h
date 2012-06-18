#ifndef CARRY_H
#define CARRY_H

uint8_t getOpcode(uint32_t instruction);
int32_t getRegisterValue(struct Processor *proc, int8_t reg);
uint32_t getMemory(struct Processor *proc, uint32_t address);
uint32_t getAddress(uint32_t instruction) ;
uint8_t getR1(uint32_t instruction);
uint8_t getR2(uint32_t instruction);
uint8_t getR3(uint32_t instruction) ;
int16_t getImmediateValue(uint32_t instruction);
void setMemory(struct Processor *proc, uint32_t address, int32_t value) ;
uint32_t getInstructionAtPC(struct Processor *proc);
int carryOutInstruction(struct Processor *processor);

#endif
