#!/bin/bash

# A script for quickly assembling valid binaries

# assemble  for mips 
#mips-linux-gnu-as -mips1 $1 -o binary.mips.elf
# Note that the assembler is too clever - it takes the assembly file and moves all J and B instructions up by one to account for the delay slot

# We then need to extract the raw binary (remove file header)
#mips-linux-gnu-objcopy -O binary -j .text binary.mips.elf binary.mips.bin


#=======Flags=======
#Provided by D.Thomas Github

MIPS_CC=mips-linux-gnu-gcc
MIPS_OBJCOPY=mips-linux-gnu-objcopy
#MIPS_OBJDUMP=mips-linux-gnu-objdump
MIPS_CPPFLAGS=(-W -Wall -O3 -fno-builtin -march=mips1 -mfp32)
MIPS_LDFLAGS=(-nostdlib -Wl,-melf32btsmip -march=mips1 -nostartfiles -mno-check-zero-division -Wl,--gpsize=0 -static -Wl,-Bstatic -Wl,--build-id=none)

#=======Script=======

for i in ./tests/*/ 
do
	for j in $i/*/
	do
		#for k in $j/*.s
		#do
		#	#Create .o file
		#	$MIPS_CC ${MIPS_CPPFLAGS[*]} -c $k -o $j/binary.mips.o
		#
		#	#Link MIPS .o with linker data to make .elf
		#	$MIPS_CC ${MIPS_CPPFLAGS[*]} ${MIPS_LDFLAGS[*]} -T linker.ld $j/binary.mips.o -o $j/binary.mips.elf
		#	#$MIPS_OBJCOPY -O binary -j --only-section=.text $j/binary.mips.elf $j/binary.mips.bin
		#	$MIPS_OBJCOPY -O binary -j .text $j/binary.mips.elf $j/binary.mips.bin
		#done
		
		if [ -e $j/assembly.s ];
		then
			k=$j/assembly.s
			#Create .o file
                        $MIPS_CC ${MIPS_CPPFLAGS[*]} -c $k -o $j/binary.mips.o
                        #Link MIPS .o with linker data to make .elf
                        $MIPS_CC ${MIPS_CPPFLAGS[*]} ${MIPS_LDFLAGS[*]} -T linker.ld $j/*.o -o $j/binary.mips.elf
                        #$MIPS_OBJCOPY -O binary -j --only-section=.text $j/binary.mips.elf $j/binary.mips.bin
                        $MIPS_OBJCOPY -O binary -j .text $j/*.elf $j/binary.mips.bin
		#else
		#	echo "Script currently requires assembly.s file to create a binary"
		fi
	done
done

