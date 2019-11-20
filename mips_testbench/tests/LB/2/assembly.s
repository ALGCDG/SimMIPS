li $1, 0x20001000
li $4, 0xFF00
sw $4, 0($1)
lb $2, 2($1) #should sign extend to -1 as loads FF from 0000FF00
addi $2, $2, 1 #gives 0
srl $2, $2, 1 #if sign extend wrong, will return 1 in top bit
jr $0
