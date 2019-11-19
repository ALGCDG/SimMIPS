bgtz $26, $L;

#code that is executed if false
addi $2, $0, 5; 
jr $0;

#code that is executed if true
$L:
addi $2, $0, 7;
jr $0; 
