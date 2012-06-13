#include "assemble.h"

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
