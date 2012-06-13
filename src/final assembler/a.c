#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

struct Data {
  char *a_instruction;
  uint32_t b_instruction[65536];
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
    if (strncmp(key,current->key,sizeof(char) * strlen(current->key))==0) {
      return current->value;
    }
    current = current->next;
  }
  free(current);
  return -1;
}

struct Table *initialiseEmptyTable(void) {
  struct Table *table = (struct Table *) malloc(sizeof(struct Table));
  table->head = NULL;
  return table;
}

struct Table *initialiseOpcodeTable(void) {
  struct Table *table = initialiseEmptyTable();
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
  char *inscpy = (char *) malloc(sizeof(char) * strlen(instruction));
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
  return atoi(reg+1);
}

int checkLabel(char *reg){
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

uint32_t parser_i(char **tokens,struct Table *labelTable, struct Table *opcodeTable, uint32_t addr){
  uint32_t opcode = getValue(tokens[0],opcodeTable);
  uint32_t immediateValue;
  uint32_t reg1Opcode = getRegisterNumber(tokens[1])<<21;
  uint32_t reg2Opcode = getRegisterNumber(tokens[2])<<16;
  if(checkHex(tokens[3])){
    immediateValue = strtol(tokens[3],NULL,16);
  } else if(checkLabel(tokens[3])) {
    immediateValue = getValue(tokens[3],labelTable);    
    if (opcode>=9 && opcode<=15) immediateValue = (immediateValue-addr)/4 ;
  }else{
    immediateValue = atoi(tokens[3]);
  }
  return ((opcode<<26) + reg1Opcode + reg2Opcode + immediateValue);
}

uint32_t parser_j(char **tokens, struct Table *labelTable, struct Table *opcodeTable){
  uint32_t address;
  uint32_t opcode = getValue(tokens[0],opcodeTable)<<26;
  if(checkLabel(tokens[1])){
    address = getValue(tokens[1],labelTable);
  } else {
    address = strtol(tokens[1],NULL,16);
  }
  return address+opcode;
}

/*
  This method reads a single line of assembly instruction from the file and put 
  it in the a_instruction element of the structure data from the given 
  file stream.
  @param fp   : specifies the file stream from which data has to eb read
  @param data : specifies the data structure in which the assembly instruction 
                read from the file has to be saved
*/
void readFromFile(FILE *fp, struct Data *data) {
  char *buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
  fgets(buffer,BUFFER_SIZE, fp);
  data->a_instruction = buffer;
}

/*
  This method writes a binary instruction in the given file stream.
  @param fp   : specifies the file stream to which the binary instruction has to
                writtten
  @param data : specifies the structure data which contains the binary 
                instruction which has to be written to the file stream given
*/
void writeToFile(char *filepath, struct Data *data) {
  FILE *fp;
  fp = fopen(filepath,"wb");
  int num_written = fwrite(data->b_instruction,sizeof(uint32_t), data->number_of_instructions, fp);
  if (num_written !=data->number_of_instructions) {
    perror("Error in writing to file");
    exit(EXIT_FAILURE);
  }
}

/*
  This method prints a 32-bit int on the terminal in base 2 with space between 
  each of the 8 bits of the 32-bit integer
  @param x : specifies the int which has to be printed on the terminal
*/
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

/*
  This method carries out the second pass on the assembly instruction returns 
  the 32-bit representation of the assembly instruction whose tokens are given.
  @param tokens : specifies the tokens of the assembly instruction starting with
                  opcode at index 0
  @param table  : specifies the structure table which is the symbol table being 
                  used for the current assembly. The  table is used to store all
                  the opcodes with their int values. Addresses of all labels are
                  also stored in the table
  @return       : returns the 32-bit representation for the instruction tokens 
                  given
*/
uint32_t pass2(char *tokens[5], struct Table *labelTable, struct Table *opcodeTable, uint32_t addr){
   if (strcmp(tokens[1],".fill")==0) {
      return atoi(tokens[2]);
    }
    ++tokens;
    char opType = getOptype(tokens[0]);
    if(opType == 'r'){
     	return parser_r(tokens, opcodeTable);
    }
    else if(opType == 'i'){
    	return parser_i(tokens,labelTable, opcodeTable , addr);
    }
    else if(opType == 'j'){
    	return parser_j(tokens, labelTable, opcodeTable);
    }
    else{
      return 0x0;
    }
}

/*
  
*/
void pass1(char *instruction, uint32_t addr, struct Table *table) {
  if (checkLabelExists(instruction)) {
    addToTable(getLabel(instruction),addr,table);
  }
}

int main(int argc, char **argv) {
  assert("Wrong Number of arguments" && argc==3);
  struct Data *data = malloc(sizeof(struct Data));
  memset(data->b_instruction,0 , 65536);
  struct Table *opcodeTable = malloc(sizeof(struct Table));
  opcodeTable = initialiseOpcodeTable();
  struct Table *labelTable = malloc(sizeof(struct Table));
  labelTable = initialiseEmptyTable();
  uint32_t address = 0;
  data->number_of_instructions = 0;  
  char *readFP = argv[1];
  char *writeFP = argv[2];

  FILE *fRead = fopen(readFP,"r");
  if (fRead==NULL) {
    perror("Error is reading from file");
    exit(EXIT_FAILURE);
  }
  
  do {    
    data->a_instruction = NULL;
    readFromFile(fRead,data);
    if (strlen(data->a_instruction)==1) goto endOfPass1While;
    pass1(data->a_instruction,address,labelTable);
    address += 4;
    data->number_of_instructions++;
    endOfPass1While: ;
    free(data->a_instruction);
  } while(feof(fRead)==0);

  //end pass 1
  rewind(fRead);
  int i = 0;
  address = 0;
  while(feof(fRead)==0) {
    data->a_instruction = NULL;
    readFromFile(fRead,data);
    if (strlen(data->a_instruction)==1) goto endOfWhilePass2;
    char *tokens[5];
    tokeniser(data->a_instruction,tokens);
    if (strcmp(".skip",tokens[1])==0) {
      printBits(0);
      printf("\t%s", data->a_instruction);
      int j = atoi(tokens[2]) - 1;
      while (j>=1) {
        printBits(0);
        printf("\n");
        --j;
      }
      i += atoi(tokens[2]);
      address = i*4;
    } else {
      data->b_instruction[i] = pass2(tokens,labelTable,opcodeTable,address); 
      printBits(data->b_instruction[i]);
      printf("\t%s\n", data->a_instruction);    
      address += 4;
      i++;
    }
    endOfWhilePass2: ;
    free(data->a_instruction);
  }
  data->number_of_instructions = i;
  writeToFile(writeFP,data);
  fclose(fRead);
}
