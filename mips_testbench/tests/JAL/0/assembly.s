$main:
jal $succ;
jr $0;

# The succ(ession) subroutine
$succ:
addi $2, $2, 1;
jr