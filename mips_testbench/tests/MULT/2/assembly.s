li $1, 0x1000;
li $3, 0x1000;
mult $1, $3;
mflo $2;
srl $2, $2, 24;
jr $0;
