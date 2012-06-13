#include "assemble.h"

char getOptype(char *opcode) {
  if (strcmp("halt", opcode)==0) {
    return '-';
  } else if (strcmp("add", opcode)==0) {
    return 'r';
  } else if (strcmp("addi", opcode)==0) {
    return 'i';
  } else if (strcmp("sub", opcode)==0) {
    return 'r';
  } else if (strcmp("subi", opcode)==0) {
    return 'i';
  } else if (strcmp("mul", opcode)==0) {
    return 'r';
  } else if (strcmp("muli", opcode)==0) {
    return 'i';
  } else if (strcmp("lw", opcode)==0) {
    return 'i';
  } else if (strcmp("sw", opcode)==0) {
    return 'i';
  } else if (strcmp("beq", opcode)==0) {
    return 'i';
  } else if (strcmp("bne", opcode)==0) {
    return 'i';
  } else if (strcmp("blt", opcode)==0) {
    return 'i';
  } else if (strcmp("bgt", opcode)==0) {
    return 'i';
  } else if (strcmp("ble", opcode)==0) {
    return 'i';
  } else if (strcmp("bge", opcode)==0) {
    return 'i';
  } else if (strcmp("jmp", opcode)==0) {
    return 'j';
  } else if (strcmp("jr", opcode)==0) {
    return 'r';
  } else if (strcmp("jal", opcode)==0) {
    return 'j';
  } else if (strcmp("out", opcode)==0) {
    return 'r';
  } else {
    return 'e';
  }  
}
