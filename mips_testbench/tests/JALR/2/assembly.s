start:
li $2, 7
li $3, subroutine1
jalr $30, $3;
end:
jr $0;

subroutine1: # add 1
addi $2, $2, 1;
li $3, subroutine2;
jalr $29, $3;
jr $30;

subroutine2: # double
sll $2, $2, 1;
li $3, subroutine3;
jalr $28, $3;
jr $29;

subroutine3: # subtract 5
addi $2, $2, -5;
jr $28;
