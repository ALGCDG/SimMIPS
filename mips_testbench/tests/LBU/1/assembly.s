li $1, 0x20001000
li $4, 0xFF00
sw $4, 0($1)
lbu $2, 2($1) #should only load 0x000000FF as loads FF from 0000FF00
addi $2, $2, 1 #gives 0x100 = 0b000100000000
srl $2, $2, 1 #gives 0x000010000000 = 128
jr $0
