uint32_t parse_fill(char **tokens, struct Table table) {
  //if : .fill operand --> that memory block is permanently assigned to operand.
  if(checkHex(tokens[2])){
    return strtol(tokens[3],NULL,16);
  } else{
    return atoi(tokens[3]);
  }
  
}

int skip(char **tokens) {
 return atoi(tokens[2]);
}


