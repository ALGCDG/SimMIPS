#register needs 2^7 2^5 2^3 2^1: 0b10000000 00100000 00001000 00000010
#memory needs   2^6 2^4 2^2 2^0: 0b01000000 00010000 00000100 00000001
#(interleving bits for unique sum)

#destination register REG2
li $2, 0b10000000001000000000100000000010

#source register (storing) REG11
li $11, 0b01000000000100000000010000000001

#memory base
li $1, 0x20000000

sw $11, 0($1)

#REMEMBER, LH should sign extend
#===============


lh $2, 2($1)
#should load 0b00000000 00000000 00000100 00000001
#so no sign extension
#4+1=5


#==============
#MASK IN REG7
li $7, 0xFF

add $3, $2, $0
and $3, $3, $7
#3 now contains just bottom byte

srl $2, $2, 8
#2 now contains second to bottom byte

add $2, $2, $3
#2 now contains sum of bytes of half word loaded in

jr $0
