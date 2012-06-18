#ifndef PRINTSEARCHREGMEM_H
#define PRINTSEARCHREGMEM_H

void printReg(struct Processor *proc , char **tokens);
void searchRegisters(struct Processor *proc, char **tokens);
void printMemory(struct Processor *proc, char **tokens);
void searchMemory(struct Processor *proc, char **tokens);
void search(struct Processor *proc,char **tokens);

#endif
