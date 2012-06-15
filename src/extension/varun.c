
void searchRegister(struct Processor *proc) {
  int start =0;
  int end = NUMBER_OF_REGISTERS;
  int value = atoi(tokens[1]);
  if (strcmp(tokens[0],"r")==0) {
    if (!checkRegister(token[2]) {
      printf("(JVG) invalid command. Please enter --help for help\n (JVG)");
      return;
    }
    if (!checkRegister(token[3]) {
      printf("(JVG) invalid command. Please enter --help for help\n (JVG)");
      return;
    }
    start = getRegisterNumber(token[2]);
    end = getRegisterNumber(tokens[3]);
  } else if (strcmp(tokens[0],"a")!=0) {
    printf("(JVG) invalid command. Please enter --help for help\n (JVG)");
    return;
  }
  printf("\n(JVG)");
  for (int i = start; i<end ; i++) {
    if (proc->gpr[i]==value) {
      printf("$%i=%i  ",i,getRegisterValue(getRegisterNumber));
    }
  }
}

void search(struct Processor *proc,char **tokens) {
  if (strcmp(token[0],"-M") ==0) {
    searchMemory(proc,tokens+1);
  } else if (strcmp(token[0],"-R")==0) {
    searchRegisters(proc,tokens+1);
  }
}

