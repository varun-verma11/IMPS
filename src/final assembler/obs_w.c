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
  if (fgets(buffer,BUFFER_SIZE, fp) == NULL) return;
  data->a_instruction = buffer;
}

/*
  This method writes a binary instruction in the given file stream.
  @param fp   : specifies the file stream to which the binary instruction has to
                writtten
  @param data : specifies the structure data which contains the binary instruction which has to be written to the 
*/
void writeToFile(FILE *fp, uint32_t ins) {
  fwrite(&ins,sizeof(uint32_t), 1, fp);
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

  //end pass 1

  rewind(fRead);
  FILE *fWrite = fopen(writeFP,"w");
  int i = 0;
  address = 0;
  while(feof(fRead)==0) {
    data->a_instruction = NULL;
    readFromFile(fRead,data);
    if (data->a_instruction == NULL) break;
    char *tokens[5];
    tokeniser(data->a_instruction,tokens);
    if (strcmp(".skip",tokens[1])==0) {
      data->b_instruction = 0;
      printBits(0);
      writeToFile(fWrite,data->b_instruction);
      printf("\t%s", data->a_instruction);
      int j = atoi(tokens[2]) - 1;
      while (j>=1) {
        printBits(0);
        writeToFile(fWrite,data->b_instruction);
        printf("\n");
        --j;
      }
      i += atoi(tokens[2]);
      address = i*4;
    } else {
      data->b_instruction = pass2(tokens,table,address);
      printBits(data->b_instruction);
      printf("\t%s", data->a_instruction);    
      address += 4;
      i++;
      writeToFile(fWrite,data->b_instruction); 
    }
    free(data->a_instruction);
  }  
  fclose(fWrite);
  fclose(fRead);
}
