#ifndef EMULATE_H
#define EMULATE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "enum.h"

#define MIN(a, b) (a > b ? b : a)




uint8_t getOpcode(uint32_t instruction);
uint32_t getAddress(uint32_t instruction);
uint8_t getR1(uint32_t instruction);
uint8_t getR2(uint32_t instruction);
uint8_t getR3(uint32_t instruction);
int16_t getImmediateValue(uint32_t instruction);
int32_t getRegisterValue(struct Processor *proc, int8_t reg);
void setMemory(struct Processor *proc, uint32_t address, int32_t value);
uint32_t getMemory(struct Processor *proc, uint32_t address);
uint32_t getInstructionAtPC(struct Processor *proc);

int carryOutInstruction(struct Processor *proc);

#endif
