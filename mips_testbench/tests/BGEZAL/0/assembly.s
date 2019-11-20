$main:
li $2, 36;
bgezal $2, $divide_by_2;
jr $0;

$divide_by_2:
sra $2, $2, 1;
jr $31;
