addi $3, $0, 0x12
li $4, 0x20000000
SB $3, 2($4)
LBU $2, 2($4)
jr $0
