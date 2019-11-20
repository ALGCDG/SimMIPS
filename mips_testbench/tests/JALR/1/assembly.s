$main:
li $8, $succ;
jalr $8;
jalr $8;
jalr $8;
jr $0;

# The succ(ession) subroutine
$succ:
addi $2, $2, 1;
jr $31;