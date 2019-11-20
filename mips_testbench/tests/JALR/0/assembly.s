$main:
li $5, $succ;
jalr $5;
jr $0;

# The succ(ession) subroutine
$succ:
addi $2, $2, 1;
jr $31;