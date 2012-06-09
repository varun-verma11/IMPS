#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 300
#define MEMORY_SIZE 65536

struct Data {
  char **a_instructions;
  uint32_t b_instructions[MEMORY_SIZE];
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
    printf("key   ----> %s     Value ----> %d \n",current->key,current->value);
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
  if(checkLabelExists(instruction)) {
    tokeniserWithLabel(instruction,tokens);
  } else {
    tokeniserWithoutLabel(instruction,tokens);
  }
}

char *getLabel(char *instruction) {
  char *inscpy = malloc(sizeof(instruction));
  inscpy =strcpy(inscpy,instruction);
  return strtok(instruction,":");
}

void pass1(char *instruction,uint32_t addr, struct Table *table) {
  if (checkLabelExists(instruction)) {
    addToTable(getLabel(instruction),addr,table);
  }
}

void readFromFile(char *filepath, struct Data *data) {
  FILE *fp;
  fp = fopen(filepath, "r");
  printf("file[path -->   %s \n",filepath); 
  if (fp==NULL) {
    perror("Error is writing to file");
    exit(EXIT_FAILURE);
  }
  printf("check 2 \n"); 
  data->a_instructions = malloc(sizeof(fp) * sizeof(char));
  char *buffer=malloc(sizeof(char)* BUFFER_SIZE);
  int i=0;
  while((feof(fp)==0) && (i<=MEMORY_SIZE)) {
    printf("%i\n", i);
    fgets(buffer,sizeof(buffer), stdin);
    data->a_instructions[i] = buffer;
    memset(&buffer,' ' , sizeof(buffer));
    i++;    
    
  }
  data ->number_of_instructions = i;
  fclose(fp); 
}

void writeToFile(char *filepath, struct Data *data) { 
  FILE *fp;
  fp = fopen(filepath, "wb");
  /*check if needed*/
  if (fp==NULL) {
    perror("Error is writing to file");
    exit(EXIT_FAILURE);
  }
	int num_of_elem_written = 0;
  int num_of_elem = data->number_of_instructions;
	num_of_elem_written = fwrite((data->b_instructions),sizeof(uint32_t), num_of_elem, fp);
	
	if (num_of_elem_written != num_of_elem) {
		perror("ERROR IN WRITING TO FILE");
		exit(EXIT_FAILURE);
 	}
  fclose(fp);
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
  char *regNumber = malloc(sizeof(char) *2);

  for(int i = 0; ; i++){
     if(i == strlen(reg)) break;
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

uint32_t parser_r(char **tokens, struct Table *table){
  uint32_t opcode = getValue(tokens[0],table)<<26;;
  uint32_t reg1Opcode = getRegisterNumber(tokens[1]) <<21;
  uint32_t reg2Opcode = getRegisterNumber(tokens[2])<<16;
  uint32_t reg3Opcode = getRegisterNumber(tokens[3])<<11;
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
      printf("%i",(x & mask) !=0);
      x<<=1;
    }
    printf("  ");
  }
  printf("\n");
}

uint32_t pass2(char *tokens[5], struct Table *table, uint32_t addr){
    if (strcmp(tokens[1],".fill")) {
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

int main(int argc, char **argv) {
  assert("Wrong Number of arguments" && argc==3);
  struct Data *data = malloc(sizeof(struct Data));
  struct Table *table = malloc(sizeof(struct Table));
  table = initialiseSymbolTable();
  uint32_t address = 0;
  data->number_of_instructions = 0;
  
  char *readFP = argv[1];
  char *writeFP = argv[2];
  
  int current_instruction = 0;
  
  readFromFile(readFP,data);
  
  while(current_instruction <= data->number_of_instructions ) {
    pass1(data->a_instructions[current_instruction],address,table);
    current_instruction++;
    address += 4;
  } 
  char **ins = data->a_instructions;
  
  while(*ins) {
    printf("%s \n",*ins);
    ins++;
  }
  
  
  current_instruction = 0;
  int i = 0;
  address = 0;
  //start pass2
  while(current_instruction <= data->number_of_instructions ) {
    char *tokens[5];
    tokeniser(data->a_instructions[current_instruction],tokens);
    if (strcmp(".skip",tokens[0])==0) {
      memset(&data->b_instructions[i], 0, sizeof(uint32_t)*atoi(tokens[2]));
      printBits(0);
      printf("    %s\n", data->a_instructions[current_instruction]);
      for(int j = 1; j<=atoi(tokens[2]);j++) {
        printBits(0);
      }
      printf("\n");
      i += atoi(tokens[2]);
      goto endWhile ;
    }
    data->b_instructions[i] = pass2(tokens,table,address);
    printBits(data->b_instructions[i]);
    printf("    %s\n", data->a_instructions[current_instruction]);
    current_instruction++;
    address += 4;
    i++;
    endWhile: ;
  }
  writeToFile(writeFP,data);
}
