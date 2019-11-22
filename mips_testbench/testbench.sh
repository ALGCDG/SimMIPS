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

if [ -w ./test/output/out.csv ]; then
	rm -r ./test/output/out.csv
fi

touch ./test/output/out.csv

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
			if [ -e $t/input.txt ] && [ ! -e $t/output.txt ]; then
				IN=$(<"$t/input.txt");
				echo $IN | $1 "$t/binary.mips.bin";
				#$IN | $1 "$t/binary.mips.bin";
				RESULT=$?
				#echo $RESULT
				if ( [ "$RESULT" = "$EXPECTATION" ] && [ ! -e $t/not.txt ] ) || ( [ ! "$RESULT" = "$EXPECTATION" ] && [ -e $t/not.txt ] ); then
					STATUS="Pass";
				else
					STATUS="Fail";
				fi
			elif [ ! -e $t/input.txt ] && [ -e $t/output.txt ]; then
				OUT=$(<"$t/output.txt");
				mkdir -p test/temp;
				$1 "$t/binary.mips.bin" > test/temp/out.txt;
				RESULT=$?;
				#echo $RESULT;
				if ( ( [ "$RESULT" = "$EXPECTATION" ] && [ ! -e $t/not.txt ] ) || ( [ ! "$RESULT" = "$EXPECTATION" ] && [ -e $t/not.txt ] ) ) && [ $(< test/temp/out.txt) = "$OUT" ]; then
					STATUS="Pass";
				else
					STATUS="Fail";
				fi
				rm test/temp/out.txt;
			elif [ -e $t/input.txt ] && [ -e $t/output.txt ]; then
				IN=$(<"$t/input.txt");
				OUT=$(<"$t/output.txt")
				mkdir -p test/temp;
				echo $IN | $1 "$t/binary.mips.bin" > test/temp/out.txt;
				RESULT=$?;
				echo $RESULT;
				if ( ( [ "$RESULT" = "$EXPECTATION" ] && [ ! -e $t/not.txt ] ) || ( [ ! "$RESULT" = "$EXPECTATION" ] && [ -e $t/not.txt ] ) ) && [ "$(< test/temp/out.txt)" = "$OUT" ]; then
					STATUS="Pass";
				else
					STATUS="Fail";
				fi
				rm test/temp/out.txt;
			fi

		else
			$1 "$t/binary.mips.bin";
        		RESULT=$?;
			#echo $RESULT;
			EXPECTATION=$(<"$t/expectation.txt");

			if ( [ "$RESULT" = "$EXPECTATION" ] && [ ! -e $t/not.txt ] ) || ( [ ! "$RESULT" = "$EXPECTATION" ] && [ -e $t/not.txt ] ) ;
      			then
      				STATUS="Pass";
      			else
        			STATUS="Fail";
      			fi
		fi
		AUTHOR_AND_MESSAGE=$(<"$t/about.txt");
	else
		AUTHOR_AND_MESSAGE="NO BIN FILE";
		STATUS="Fail";
	fi
	cs=", ";
	if [ "$STATUS" = "Fail" ]; then
		FAIL_MSG="[EXPECTED ${EXPECTATION} BUT GOT ${RESULT}]   "
	else
		FAIL_MSG=""
	fi
        echo "${TestID}${cs}${testType}${cs}${STATUS}${cs}${AUTHOR_AND_MESSAGE}${FAIL_MSG}";
				mkdir -p test/output;
	echo "${TestID}${cs}${testType}${cs}${STATUS}${cs}${AUTHOR_AND_MESSAGE}${FAIL_MSG}" >> ./test/output/out.csv;
    done
    #printf "\n=============================================================================\n";
done
