#!/bin/bash

# A script for quickly creating tests and valid binaries

mips-linux-gnu-gcc -static -nostdlib -O3 $1 -o binary.mips.elf
# We then need to extract the raw binary (remove file header)
mips-linux-gnu-objcopy -O binary -j .text binary.mips.elf binary.mips.bin

