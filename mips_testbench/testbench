#!/bin/bash

# Adding Unofficial Strict Mode
set -uo pipefail
IFS=$'\n\t'

echo "Running testbench..."

# testing return codes
# file should be csv and have fields, input binary, purpose of test (which instruction we are testing), expected output code, author
# tests = $( cat test_file.csv )
# file | grep -o "hello,"

# cat filename | while read LINE; do
#     echo $LINE
# done
# # testing character outputs

# for Instruction in "find . -type d"
# do
#     for Test in "find . -type d"
#     do
#         bin/mips_simulator binary.bin
#         RESULT = echo $?;
#         if $RESULT == expectation.txt
#         do
#             echo "Pass"
#         else
#         do
#             echo "Fail"
#         done
#         cat about.txt
#     done
# done

if [ -w ./testing/out.csv ]; then
	rm -r ./testing/out.csv
fi

touch ./testing/out.csv

for i in ./mips_testbench/tests/*/  #for each directory in the tests folder
do
    #cd $i
    for t in $i/*/  #for each test in the folder (t)
    do
	testType=$(echo "$i" | cut -d/ -f4)
	testNum=$(echo "$t" | cut -d/ -f6)
	TestID="${testType}${testNum}";
	if [ -e $t/binary.mips.bin ];
	then
        	if [ -e $t/input.txt ] || [ -e $t/output.txt ];
		then
			EXPECTATION=$(<"$t/expectation.txt");
			if [ -e $t/input.txt ] && ![ -e $t/output.txt ]; then
				IN=$(<"$t/input.txt");
				echo $IN | $1 "$t/binary.mips.bin";
				RESULT=$?
				echo $RESULT
				if [ "$RESULT" = "$EXPECTATION" ]; then
					STATUS="PASS";
				else
					STATUS="FAIL";
				fi
			elif ![ -e $t/input.txt ] && [ -e $t/output.txt ]; then
				OUT=$(<"$t/output.txt");
				$1 "$t/binary.mips.bin" | read GOTOUT;
				RESULT=$?;
				echo $RESULT;
				if [ "$RESULT" = "$EXPECTATION" ] && [ "$GOTOUT" = "OUT" ]; then
                                        STATUS="PASS";
                                else
                                        STATUS="FAIL";
                                fi
			elif [ -e $t/input.txt ] && [ -e $t/output.txt ]; then
				IN=$(<"$t/input.txt");
				OUT=$(<"$t/output.txt")
				echo $IN | $1 "$t/binary.mips.bin" | read GOTOUT;
				RESULT=$?;
				echo $RESULT;
				if [ "$RESULT" = "$EXPECTATION" ] && [ "$GOTOUT" = "OUT" ]; then
					STATUS="PASS";
				else
					STATUS="FAIL";
				fi
			fi

		else
			$1 "$t/binary.mips.bin";
        		RESULT=$?;
			echo $RESULT;
			EXPECTATION=$(<"$t/expectation.txt");
		
			if [ "$RESULT" = "$EXPECTATION" ];
      			then
      				STATUS="Pass";
      			else
        			STATUS="Fail";
      			fi
		fi
		AUTHOR_AND_MESSAGE=$(<"$t/about.txt");
	else
		AUTHOR_AND_MESSAGE="NO BIN FILE";
		STATUS="FAIL";
	fi
	cs=", ";
        echo "${TestID}${cs}${testType}${cs}${STATUS}${cs}${AUTHOR_AND_MESSAGE}";
	echo "${TestID}${cs}${testType}${cs}${STATUS}${cs}${AUTHOR_AND_MESSAGE}" >> ./testing/out.csv;
    done
    printf "\n=============================================================================\n";
done
