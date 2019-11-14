#!/bin/bash

# A script for quickly compiling valid binaries

# cross compile for mips 
mips-linux-gnu-gcc -static -nostdlib -O3 -mips1 -mfp32 $1 -o binary.mips.elf
# We then need to extract the raw binary (remove file header)
mips-linux-gnu-objcopy -O binary -j .text binary.mips.elf binary.mips.bin

