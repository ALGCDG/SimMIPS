li $7, 0x80000000;
li $8, 0x2;
divu $7, $8;
mfhi $2;
srl $2, $2, 28;
jr $0;
