lui $1, 0xffff;
addi $1, $1, 0xffff; # $1 contains -1
lui $3, 0x8000; # $3 contains the largest negative number
add $2, $3, $1; # su ought to be 0x17FFFFFFF, but this reduced to 32 bits is positive
jr $0;
#NB, we shouldn't need any JR to zero, as the exception ought to terminate the simulator
