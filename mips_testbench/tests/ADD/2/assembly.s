lui $1, 0xffff;
addi $1, $1, 0xffff; # $1 contains -1
lui $3, 0x8000; # $3 contains the largest negative number
add $2, $3, $1;
#NB, we shouldn't need any JR to zero, as the exception ought to terminate the simulator
