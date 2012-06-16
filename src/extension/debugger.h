#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define NUMBER_OF_COMMANDS 7
#define BUFFER_SIZE 300      
                
char debugInstructions[][NUMBER_OF_COMMANDS] = {"list","stp","reg","mem","search","pc", "run"};

#endif
