#ifndef CHECKS_H
#define CHECKS_H


int checkRegister(char *token);
int getRegisterNumber(char *reg);
int checkIfNumber(char *num);
int checkAllRegistersAreValid(char **regs);
int checkIfAllMemoryLocationsAreValid(char **tokens);
int checkIfBreakPoint(int *breakPoints, int lineNumber);
int checkRtypeInstructionIsValid(uint32_t ins);
int checkBrachInstructionIsValid(uint32_t ins, struct Processor *proc);
int checkItypeInstructionIsValid(uint32_t ins);
int checkJtypeIsValid(uint32_t ins);
int checkIfLoadAndStoreAreValid(uint32_t ins);
int checkIfInstructionIsValid(struct Processor *processor);
int checkUserCommandIsValid(char *command);




#endif
