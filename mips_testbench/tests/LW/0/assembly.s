addi $2, $0, 0x00000001; #loading in a simple literal
sll $2, $2, 29; #shifting left to get registery value 0x20000000
lw $2, $2;
jr $0;
