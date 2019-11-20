$main:
li $2, 6;
bltzal $2, $divide_by_2;
jr $0;

$divide_by_2:
addi $2, $2, 1;
jr $31;
