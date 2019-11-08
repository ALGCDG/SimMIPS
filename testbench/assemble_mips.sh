#!/bin/bash

# A script for quickly assembling valid binaries

# assemble  for mips 
mips-linux-gnu-as -mips1 $1 -o binary.mips.elf
# Note that the assembler is too clever - it takes the assembly file and moves all J and B instructions up by one to account for the delay slot

# We then need to extract the raw binary (remove file header)
mips-linux-gnu-objcopy -O binary -j .text binary.mips.elf binary.mips.bin

