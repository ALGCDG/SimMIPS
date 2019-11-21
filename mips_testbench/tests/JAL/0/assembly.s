_entry:
jal _succ;
jr $0;

# The succ(ession) subroutine
_succ:
addi $2, $2, 1;
jr $31;
