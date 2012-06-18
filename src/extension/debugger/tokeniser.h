#ifndef TOKENISER_H
#define TOKENSIER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

int checkLabelExists(char *instruction);
void tokeniserWithoutLabel(char *instruction,char *tokens[5]);
void tokeniserWithLabel(char *instruction,char *tokens[5]);
void tokeniser(char *instruction, char *tokens[5]);

#endif
