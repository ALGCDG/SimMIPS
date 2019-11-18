#!/bin/bash

# A script for quickly assembling valid binaries

# assemble  for mips 
#mips-linux-gnu-as -mips1 $1 -o binary.mips.elf
# Note that the assembler is too clever - it takes the assembly file and moves all J and B instructions up by one to account for the delay slot

# We then need to extract the raw binary (remove file header)
#mips-linux-gnu-objcopy -O binary -j .text binary.mips.elf binary.mips.bin


for i in ./tests/*/ 
do
	for j in $i/*/
	do
		for k in $j/*.s
		do
			mips-linux-gnu-as -mips1 $k -o $j/binary.mips.elf
			mips-linux-gnu-objcopy -O binary -j .text $j/binary.mips.elf $j/binary.mips.bin
		#printf "$j\n"
		done
	done
done

