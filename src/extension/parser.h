#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "table.h"

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

char *getLabel(char *instruction);
int checkHex(char *reg);
uint32_t parse_fill(char **tokens, struct Table table);
int getRegisterNumber(char *reg);
int checkLabel(char *reg);
int checkRegister(char *token);
uint32_t parser_r(char **tokens, struct Table *table);
uint32_t parser_i(char **tokens,struct Table *labelTable, struct Table *opcodeTable, uint32_t addr);
uint32_t parser_j(char **tokens, struct Table *labelTable, struct Table *opcodeTable);

#endif
