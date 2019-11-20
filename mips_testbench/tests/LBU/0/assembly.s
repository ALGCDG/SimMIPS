li $3, 0xFF
li $4, 0x20000000
sb $3, 0($4)
lbu $2, 0($4)
addi $2, $2, 1
srl $2, $2, 1
jr $0
