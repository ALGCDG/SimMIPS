li $3, 0x10000001;
li $4, 0x10000000;
# the result should be 0x1000000_00000000 + 0x10000000 = 0x1000000_10000000
mult $3, $4;
mfhi $2;
srl $2, 6; 
jr $0;
