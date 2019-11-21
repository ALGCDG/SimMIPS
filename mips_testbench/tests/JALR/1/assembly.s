.text
$main:
li $8, 0x10000000
addi $8, $8, $succ;
jalr $8;
jalr $8;
jalr $8;
jr $0;

# The succ(ession) subroutine
$succ:
addi $2, $2, 1;
jr $31;
