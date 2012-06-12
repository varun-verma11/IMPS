#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

struct Data {
  char *a_instruction;
  uint32_t b_instruction;
  int number_of_instructions;
};

enum opCodes {HALT=0, ADD, ADDI, SUB, SUBI, MUL, MULI, LW, SW, BEQ, BNE, BLT, BGT, BLE, 
                BGE, JMP, JR, JAL, OUT};

struct Table_Elem {
  int value;
  struct Table_Elem *next;
  char *key;
};

struct Table {
  struct Table_Elem *head;
};

void addToTable(char *key, int value, struct Table *table) {
  struct Table_Elem *new_elem = (struct Table_Elem *) malloc(sizeof(struct Table_Elem));
	new_elem->key = key;
  new_elem->value = value;
  new_elem->next = table->head;
  table->head = new_elem;
}

int getValue(char *key, struct Table *table) {
  struct Table_Elem *current = table->head;  
  while(current!=NULL) {
    if (strcmp(key,current->key)==0) return current->value;
    current = current->next;
  }
  return -1;
}

struct Table *initialiseSymbolTable(void) {
  struct Table *table = (struct Table *) malloc(sizeof(struct Table));
  table->head = NULL;
  addToTable("halt",0,table);
  addToTable("add", 1,table);
  addToTable("addi",2,table);
  addToTable("sub",3,table);
  addToTable("subi",4,table);
  addToTable("mul",5,table);
  addToTable("muli",6,table);
  addToTable("lw",7,table);
  addToTable("sw",8,table);
  addToTable("beq",9,table);
  addToTable("bne",10,table);
  addToTable("blt",11,table);
  addToTable("bgt",12,table);
  addToTable("ble",13,table);
  addToTable("bge",14,table);
  addToTable("jmp",15,table);
  addToTable("jr",16,table);
  addToTable("jal",17,table);
  addToTable("out",18,table);
  return table;
}


int checkLabelExists(char *instruction) {
  return strchr(instruction,58)!=NULL ;
}

void tokeniserWithoutLabel(char *instruction,char *tokens[5]) {
  char *token;
  int count =1;
  token = strtok(instruction, " ");
  tokens[count] = token;
  do {
    count++;
    token = strtok(NULL, " ");
    tokens[count] = token;
  } while (count!=5);
}

void tokeniserWithLabel(char *instruction,char *tokens[5]) {
  char *token;
  int count =0;
  token = strtok(instruction, ":");
  do {
    tokens[count] = token;
    token = strtok(NULL, " ");
    count++;
  } while (count!=5);
}

void tokeniser(char *instruction, char *tokens[5]) {
  char *inscpy = (char *) malloc(sizeof(instruction));
  inscpy =strcpy(inscpy,instruction);
  if(checkLabelExists(inscpy)) {
    tokeniserWithLabel(inscpy,tokens);
  } else {
    tokeniserWithoutLabel(inscpy,tokens);
  }
}

char *getLabel(char *instruction) {
  char *inscpy = (char *) malloc(sizeof(instruction));
  inscpy =strcpy(inscpy,instruction);
  return strtok(inscpy,":");
}

void readFromFile(FILE *fp, struct Data *data) {
  char *buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
  if (fgets(buffer,BUFFER_SIZE, fp) == NULL) return;
  data->a_instruction = buffer;
}

void writeToFile(FILE *fp, uint32_t ins) {
  fwrite(&ins,sizeof(uint32_t), 1, fp);
}

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

int checkHex(char *reg){
  char *hex = "0x";
  char *regs = (char *) malloc(sizeof(char) *3);
  regs = strncpy(regs,reg,2);
  if(strcmp(hex , regs)==0) return 1;
  return 0;
}

uint32_t parse_fill(char **tokens, struct Table table) {
  //if : .fill operand --> that memory block is permanently assigned to operand.
  if(checkHex(tokens[2])){
    return strtol(tokens[3],NULL,16);
  } else{
    return atoi(tokens[3]);
  }
  
}

int getRegisterNumber(char *reg){
  char *regNumber = (char *) malloc(sizeof(char) *2);
  for(int i = 0; ; i++){
     if(i >= strlen(reg)) break;
     regNumber[i] = reg[i+1];
  }
  return atoi(regNumber);

}

int checkLabel(char *reg){
 //if(strlen(&reg)){
  if((strcmp("a", reg)<=0 && strcmp(reg, "{")<0) || 
      (strcmp("A", reg)<=0 && strcmp("[", reg)>0)) 
  return 1;
  return 0; 
}
int checkRegister(char *token){
 return (token!=NULL) ? (token[0]=='$') : 0;
}

uint32_t parser_r(char **tokens, struct Table *table){
  uint32_t opcode = getValue(tokens[0],table)<<26;
	uint32_t reg1Opcode = (checkRegister(tokens[1])) ? getRegisterNumber(tokens[1]) <<21 : 0;
	uint32_t reg2Opcode = (checkRegister(tokens[2])) ? getRegisterNumber(tokens[2]) <<16 : 0;
	uint32_t reg3Opcode = (checkRegister(tokens[3])) ? getRegisterNumber(tokens[3]) <<11 : 0;
	return (opcode + reg1Opcode + reg2Opcode + reg3Opcode);
}

uint32_t parser_halt(char **tokens,struct Table *table) {
  return 0x0;
}

uint32_t parser_i(char **tokens,struct Table *table){
  uint32_t opcode = getValue(tokens[0],table)<<26;
  uint32_t immediateValue;
  uint32_t reg1Opcode = getRegisterNumber(tokens[1])<<21;
  uint32_t reg2Opcode = getRegisterNumber(tokens[2])<<16;

  if(checkHex(tokens[3])){
    immediateValue = (int) strtol(tokens[3],NULL,16);
  } else if(checkLabel(tokens[3])){
    immediateValue = (int) getValue(tokens[3], table);
  }else{
    immediateValue = atoi(tokens[3]);
  }
  return (opcode + reg1Opcode + reg2Opcode + immediateValue);
}

uint32_t parser_j(char **tokens, struct Table *table){
  uint32_t address;
  uint32_t opcode = getValue(tokens[0],table)<<26;
  if(checkLabel(tokens[1])){
    address = getValue(tokens[1],table);
  } else {
    address = *tokens[1];
  }
  return address+opcode;
}

void printBits(uint32_t x) {
  int i,j;
  uint32_t mask = 1<<31;
  for(j=0;j<4;++j) {
    for (i=0*j;i<8;++i) {
      printf("%i ",(x & mask) !=0);
      x<<=1;
    }
    printf("  ");
  }
}

uint32_t pass2(char *tokens[5], struct Table *table, uint32_t addr){
   if (strcmp(tokens[1],".fill")==0) { 
      addToTable(tokens[0],atoi(tokens[2]), table);
      return atoi(tokens[2]);
    }
    ++tokens;
    char opType = getOptype(tokens[0]);
    if(opType == 'r'){
     	return parser_r(tokens, table);
    }
    else if(opType == 'i'){
    	return parser_i(tokens, table);
    }
    else if(opType == 'j'){
    	return parser_j(tokens, table);
    }
    else{
     return 0x0;
    }
}

void pass1(char *instruction, uint32_t addr, struct Table *table) {
  if (checkLabelExists(instruction)) {
    addToTable(getLabel(instruction),addr,table);
  }
}

int main(int argc, char **argv) {
  assert("Wrong Number of arguments" && argc==3);
  struct Data *data = malloc(sizeof(struct Data));
  struct Table *table = malloc(sizeof(struct Table));
  table = initialiseSymbolTable();
  uint32_t address = 0;
  data->number_of_instructions = 0;  
  char *readFP = argv[1];
  char *writeFP = argv[2];
  
  //int current_instruction = 0;


  //start pass 1+
  FILE *fRead = fopen(readFP,"r");
  if (fRead==NULL) {
    perror("Error is reading from file");
    exit(EXIT_FAILURE);
  }
  
  
  do {    
    data->a_instruction = NULL;
    readFromFile(fRead,data);
    if (data->a_instruction == NULL) break;
    pass1(data->a_instruction,address,table);
    address += 4;
    data->number_of_instructions++;
    free(data->a_instruction);
  } while(feof(fRead)==0);
  printf("end of pass 1 \n");

  //end pass 1

  rewind(fRead);
  FILE *fWrite = fopen(writeFP,"w");
  int i = 0;
  address = 0;
  //start pass2
  while(feof(fRead)==0) {
    data->a_instruction = NULL;
    readFromFile(fRead,data);
    if (data->a_instruction == NULL) break;
    char *tokens[5];
    tokeniser(data->a_instruction,tokens);
    if (strcmp(".skip",tokens[0])==0) {
      data->b_instruction = 0;
      printBits(0);
      writeToFile(fWrite,data->b_instruction);
      printf("\t%s\n", data->a_instruction);
      for(int j = 1; j<=atoi(tokens[2]);j++) {
        printBits(0);
        writeToFile(fWrite,data->b_instruction);
      }
      printf("\n");
      i += atoi(tokens[2]);
      address = (i-1)*4;
      goto endWhile ;
    }
    data->b_instruction = pass2(tokens,table,address);
    printBits(data->b_instruction);
    printf("\t%s\n", data->a_instruction);    
    address += 4;
    i++;
    writeToFile(fWrite,data->b_instruction);
    endWhile: ;
  }  
  fclose(fWrite);
  fclose(fRead);
}
