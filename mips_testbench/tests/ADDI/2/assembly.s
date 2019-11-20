li $1, 0x80000000; # largest negative number
addi $2, $1, -1; # cpu cant represent the largest negative number minus one
jr $0;
#NB, we shouldn't need any JR to zero, as the exception ought to terminate the simulator
