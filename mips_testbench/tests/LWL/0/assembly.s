addi $10, $0, 1
addi $11, $0, 4
addi $12, $0, 16
addi $13, $0, 64

sll $10, $10, 24
sll $11, $11, 16
sll $12, $12, 8
#sll $13, $13, 0

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
# 1 4 16 64 | 4 5 6 7 | 0 0 0 0

#===========

#want to interleve bits

#                  1         4         16      64
#mem contains 0b00000001 00000100 00010000 01000000
#reg needs    0b00000010 00001000 00100000 10000000
#                  2         8         32      128

li $3, 0b00000010000010000010000010000000

#===========
#below is test specific
#=================


#LWL RESULT IN REG 3

lwl $3, 0($1)
#expect 1 4 16 64 in each byte of 3


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
