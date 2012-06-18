#ifndef EMULATE_H
#define EMULATE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "enum.h"

#define MIN(a, b) (a > b ? b : a)




void binaryFileLoader(char *filepath, struct Processor *processor);
void dumpProcessor(struct Processor *proc);


#endif
