lui $26, 0xf0ff;
lui $25, 0xfff0;
bne $26, $25, $L2;

#code that is executed if false
$L1:
addi $2, $0, 5; 
jr $0;

#code that is executed if true
$L2:
addi $2, $0, 7;
jr $0; 
