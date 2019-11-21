#!/bin/bash

# A script for quickly compiling valid binaries

# # cross compile for mips 
# mips-linux-gnu-gcc -static -nostdlib -O3 -mips1 -mfp32 $1 -o binary.mips.elf
# # We then need to extract the raw binary (remove file header)
# mips-linux-gnu-objcopy -O binary -j .text binary.mips.elf binary.mips.bin


#Provided by D.Thomas Github

MIPS_CC=mips-linux-gnu-gcc
MIPS_OBJCOPY=mips-linux-gnu-objcopy
#MIPS_OBJDUMP=mips-linux-gnu-objdump
MIPS_CPPFLAGS=( -W -Wall -fno-builtin -march=mips1 -mfp32)
MIPS_LDFLAGS=(-nostdlib -Wl,-melf32btsmip -march=mips1 -nostartfiles -mno-check-zero-division -Wl,--gpsize=0 -static -Wl,-Bstatic -Wl,--build-id=none)


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
		if [ -e $j/src.c ];
		then
			k=$j/src.c
			#Create .o file
                        $MIPS_CC ${MIPS_CPPFLAGS[*]} -c $k -o $j/binary.mips.o
                        #Link MIPS .o with linker data to make .elf
                        $MIPS_CC ${MIPS_CPPFLAGS[*]} ${MIPS_LDFLAGS[*]} -T linker.ld stack_stub.o  $j/*.o -o $j/binary.mips.elf
                        # $MIPS_CC ${MIPS_CPPFLAGS[*]} ${MIPS_LDFLAGS[*]} -T linker.ld $j/*.o stack_stub.o -o $j/binary.mips.elf
                        # $MIPS_OBJCOPY -O binary -j --only-section=.text $j/binary.mips.elf $j/binary.mips.bin
                        $MIPS_OBJCOPY -O binary -j .text $j/*.elf $j/binary.mips.bin


						# my attempt to fix
						# # cross compile for mips 
						# mips-linux-gnu-gcc -static -nostdlib -O3 -mips1 -mfp32 $k stack_stub.s -o $j/binary.mips.elf
						# # We then need to extract the raw binary (remove file header)
						# mips-linux-gnu-objcopy -O binary -j .text $j/binary.mips.elf $j/binary.mips.bin
		#else
		#	echo "Script currently requires assembly.s file to create a binary"
		fi
	done
done
