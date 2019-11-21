#register needs 2^6 2^4 2^2 2^0  0b01000000 00010000 00000100 00000001
#memory needs   2^7 2^5 2^3 2^1: 0b10000000 00100000 00001000 00000010
#(interleving bits for unique sum, giving memory active top bit to test sign extension)

#destination register REG2
li $2, 0b01000000000100000000010000000001

#source register (storing) REG11
li $11, 0b10000000001000000000100000000010

#memory base
li $1, 0x20000000

sw $11, 0($1)

#REMEMBER, LH should sign extend
#===============


lhu $2, 0($1)

#loading top half: 1000000000100000
#high bit 15 should mean that extend to 0b0000000000000000 1000000000100000
#add to this number 0111111111100000 should result in 10000000000000000 in the register
#so shift right by 16

srl $2, $2, 16

#==============
jr $0
