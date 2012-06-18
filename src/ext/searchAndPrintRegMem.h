#ifndef SEARCH_H
#define SEARCH_H

void printReg(struct Processor *proc , char **tokens);
void searchRegisters(struct Processor *proc, char **tokens) ;
void printMemory(struct Processor *proc, char **tokens) ;
void searchMemory(struct Processor *proc, char **tokens) ;
void search(struct Processor *proc,char **tokens);

#endif
