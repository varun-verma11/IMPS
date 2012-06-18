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
                    

                    add $5 $0 $0
row_loop:           bge $5 $1 end_r_loop
                    add $6 $0 $0

col_loop:           bge $6 $2 end_c_loop              
                    add $7 $0 $0

sq_r_loop:          bge $7 $3 end_sr_loop
                    add $8 $0 $0

sq_c_loop:          bge $8 $4 end_sc_loop
                    
                    
                    
end_sc_loop:  
             addi $7 $7 1                       - m++
             jmp sq_r_loop

end_sr_loop: 
             addi $6 $6 1                       - j++
             beq $9 w_b w_to_b1
             beq $9 b_b b_to_w1

             
end_c_loop:  addi $5 $5 1                 - i++
             beq $9 w_b w_to_b2
             beq $9 b_b b_to_w2

w_to_b2:     addi $9 $0 w_g               - $9 = r component of paint
             addi $10 $0 w_g              - $10 = g component of paint
             addi $11 $0 w_b              - $11 = b component of paint
             jmp row_loop

b_to_w2:     addi $9 $0 b_g               - $9 = r component of paint
             addi $10 $0 b_g              - $10 = g component of paint
             addi $11 $0 b_b              - $11 = b component of paint
             jmp row_loop

end_r_loop:  sw $15 $10 w_b


print:              beq $

print255:           addi $1 $0 50 -Load $1 with ascii value for 2
                    out $1 -Print value for 2
                    addi $1 $0 50 -Load $1 with ascii value for 5
                    out $1 -Print value for 5
                    addi $1 $0 50 -Load $1 with ascii value for 5
                    out $1 -Print value for 5
                    jmp ____ -go back to loop

print0:             addi $1 $0 48 -Load $1 with ascii value for 0
                    out $1 -Print value for 0
                    49,1 Botw
                    
