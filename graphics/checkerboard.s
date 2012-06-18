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

start_loop:       addi $1 $0 board_row
                  addi $2 $0 board_col
                  addi $3 $0 square_row
                  addi $4 $0 square_column
                  addi $9 $0 w_g                - $9 = r component of paint (set to white)
                  addi $10 $0 w_g               - $10 = g component of paint (set to white)
                  addi $11 $0 w_b               - $11 = b component of paint (set to white)
                  addi $15 $0 255
                  addi $16 $0 0
                  add $5 $0 $0
             
row_loop:    bge $5 $1 end_r_loop
             add $6 $0 $0

col_loop:    bge $6 $2 end_c_loop           
             add $7 $0 $0

sq_r_loop:   bge $7 $3 end_sr_loop
             add $8 $0 $0

sq_c_loop:   bge $8 $4 end_sc_loop
             add $12 $0 $9                     - $12 = r component of paint
             add $13 $0 $10                    - $13 = g component of paint
             add $14 $0 $11                    - $14 = b component of paint
getr:        jmp printr                      
getg:        jmp printg
getb:        jmp printb
continue:    addi $8 $8 1                      - n++
             jmp sq_c_loop

end_sc_loop: jmp swap_colours1
ret_swap1:   addi $7 $7 1                      - m++
             jmp sq_r_loop

end_sr_loop: jmp swap_colours2
ret_swap2:   addi $6 $6 1                      - j++
             jmp col_loop
             
end_c_loop:  addi $5 $5 1                      - i++
             jump row_loop 
              
end_r_loop:  halt
             
             
printr:       beq $9 $15 printr255
RB:           beq $9 $16 printr0
              jmp getg
printg:       beq $10 $15 printg255
GB:           beq $10 $16 printg0
              jmp getb
printb:       beq $10 $15 printb255
BB:           beq $10 $16 printb0
              jmp continue
printr255:    addi $17 $0 50                   - Load $17 with ascii value for 2
              out $17                          - Print value for 2
              addi $17 $0 53                   - Load $17 with ascii value for 5
              out $17                          - Print value for 5
              addi $17 $0 53                   - Load $17 with ascii value for 5
              out $17                          - Print value for 5
              jmp RB                           - Go back to loop

printg255:    addi $17 $0 50                   - Load $17 with ascii value for 2
              out $17                          - Print value for 2
              addi $17 $0 53                   - Load $17 with ascii value for 5
              out $17                          - Print value for 5
              addi $17 $0 53                   - Load $17 with ascii value for 5
              out $17                          - Print value for 5
              jmp GB                           - Go back to loop              
              
printb255:    addi $17 $0 50                   - Load $17 with ascii value for 2
              out $17                          - Print value for 2
              addi $17 $0 53                   - Load $17 with ascii value for 5
              out $17                          - Print value for 5
              addi $17 $0 53                   - Load $17 with ascii value for 5
              out $17                          - Print value for 5
              jmp BB                           - Go back to loop             
    
printr0:      addi $17 $0 48                   - Load $1 with ascii value for 0
              out $17                          - Print value for 0
              jmp getg

printg0:      addi $17 $0 48                   - Load $1 with ascii value for 0
              out $17                          - Print value for 0
              jmp getb
              
printb0:      addi $17 $0 48                   - Load $1 with ascii value for 0
              out $17                          - Print value for 0
              jmp continue
              
swap_colours1: beq $9 $15 swapb1
               beq $9 $16 swapw1
swapb1:        add $9 $0 $16
               jmp ret_swap1
swapw1:        add $9 $0 $15
               jmp ret_swap1 

swap_colours2: beq $9 $15 swapb2
               beq $9 $16 swapw2
swapb2:        add $9 $0 $16
               jmp ret_swap2
swapw2:        add $9 $0 $15
               jmp ret_swap2            
             
             
square_row:  .fill 8                          - Size in pixels of one row inside a square
square_col:  .fill 8                          - Size in pixels of one column inside a square
board_row:   .fill 8                          - Number of rows on the board.
board_col:   .fill 8                          - Number of columns on the board.
w_r:         .fill 255                        - Decimal representation of white's r value
w_g:         .fill 255                        - Decimal representation of white's g value
w_b:         .fill 255                        - Decimal representation of white's b value
b_r:         .fill 0                          - Decimal representation of black's r value
b_g:         .fill 0                          - Decimal representation of black's g value
b_b:         .fill 0                          - Decimal representation of black's b value
