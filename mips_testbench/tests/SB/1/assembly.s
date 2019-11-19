li $3, 0xFFFF
li $4, 0x20000000
sb $3, 0($4)
lbu $2, 0($4)
jr $0
