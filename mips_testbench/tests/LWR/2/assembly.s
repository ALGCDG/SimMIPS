addi $11, $0, 1
addi $12, $0, 2
addi $13, $0, 3
#0 in 10

sll $11, $11, 16
sll $12, $12, 8
#0 is 'shifted' 24

or $2, $10, $11
or $2, $2, $12
or $2, $2, $13

li $1, 0x20000000

sw $2, 0($1)

#===========

addi $10, $0, 4
addi $11, $0, 5
addi $12, $0, 6
addi $13, $0, 7

sll $10, $10, 24
sll $11, $11, 16
sll $12, $12, 8
#sll $13, $13, 0

or $2, $10, $11
or $2, $2, $12
or $2, $2, $13

sw $2, 4($1) #WORD ARE STORED CORRECTLY

#===========

#mem now looks like
#0x20000000 -> increasing address
# 0 1 2 3 | 4 5 6 7 | 0 0 0 0

#===========

li $3, 0x0a0000

#===========
#below is test specific
#=================


#LWL RESULT IN REG 3

lwr $3, 2($1)
#expect 0 1 2 3 in each byte of 2


#=================
#below is general
#===========

#BYTE MASK IN REG 5:
li $5, 0xFF

and $4, $5, $3
add $2, $0, $4

srl $3, $3, 8
and $4, $5, $3
add $2, $2, $4

srl $3, $3, 8 
and $4, $5, $3 
add $2, $2, $4 
 
srl $3, $3, 8 
and $4, $5, $3 
add $2, $2, $4 

jr $0
