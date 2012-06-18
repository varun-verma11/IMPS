start_check_board:  addi $1 $0 80               - Load $1 with ascii value for P
                    out $1                      - Print value for P
                    addi $1 $0 54               - Load $1 with ascii value for 6
                    out $1                      - Print value for 6
                    addi $1 $0 51               - Load $1 with ascii value for 3
                    out $1                      - Print value for 3
                    addi $1 $0 50               - Load $1 with ascii value for 2
                    out $1                      - Print value for 2
                    addi $1 $0 54               - Load $1 with ascii value for 6
                    out $1                      - Print value for 6
                    addi $1 $0 52               - Load $1 with ascii value for 4
                    out $1                      - Print value for 4
                    addi $1 $0 51               - Load $1 with ascii value for 3
                    out $1                      - Print value for 3
                    addi $1 $0 50               - Load $1 with ascii value for 2
                    out $1                      - Print value for 2
                    addi $1 $0 54               - Load $1 with ascii value for 6
                    out $1                      - Print value for 6
                    addi $1 $0 52               - Load $1 with ascii value for 4
                    out $1                      - Print value for 4
                    addi $1 $0 51               - Load $1 with ascii value for 3
                    out $1                      - Print value for 3
                    addi $1 $0 50               - Load $1 with ascii value for 2
                    out $1                      - Print value for 2
                    addi $1 $0 50               - Load $1 with ascii value for 2
                    out $1                      - Print value for 2
                    addi $1 $0 53               - Load $1 with ascii value for 5
                    out $1                      - Print value for 5
                    addi $1 $0 53               - Load $1 with ascii value for 5
                    out $1                      - Print value for 5
                    addi $1 $0 51               - Load $1 with ascii value for 3
                    out $1                      - Print value for 3
                    addi $1 $0 50               - Load $1 with ascii value for 2
                    out $1                      - Print value for 2

                    addi $30 $0 8
                    addi $29 $0 4
                    


megaloop1_start:    beq $28 $29 megaloop1_end

loop1_start:        beq $2 $30 loop1_end
                    
loop1_body:         addi $1 $0 50               - Load $1 with ascii value for 2
                    out $1                      - Print value for 2
                    addi $1 $0 53               - Load $1 with ascii value for 5
                    out $1                      - Print value for 5
                    addi $1 $0 53               - Load $1 with ascii value for 5
                    out $1                      - Print value for 5
                    addi $2 $0 1
                    jmp loop1_body
                    
loop1_end:          addi $2 $0 0                    
                    
loop2_start:        beq $2 $30 loop2_end       
                    
loop2_body:         addi $1 $0 48               - Load $1 with ascii value for 0
                    out $1                      - Print value for 2
                    addi $3 $0 1
                    jmp loop2_start

loop2_end:          addi $2 $0 0                    

                    addi $28 $29 1
                    jmp megaloop1_start

megaloop1_end:      addi $28 $0 0

                    
