#ifndef VARUN_H
#define VARUN_H

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int checkIfNumber(char *num);
int checkAllRegistersAreValid(char **regs);
void printInvalidCommandMessage(void);
void searchRegister(struct Processor *proc, char **tokens);
int checkIfAllMemoryLocationsAreValid(char **tokens);
void printMemory(struct Processor *proc, char **tokens);
void searchMemory(struct Processor *proc, char **tokens);
void search(struct Processor *proc,char **tokens);


#endif
