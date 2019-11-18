lui $26, 0xffff;
lui $25, 0xffff;
bne $26, $25, 8;

#code that is executed if false
addi $2, $0, 5; 
jr $0;

#code that is executed if true
addi $2, $0, 7;
jr $0; 
