#!/bin/bash

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

cd ..;
for i in ./mips_testbench/tests/*/  #for each directory in the tests folder
do
    #cd $i
    for t in $i/*/  #for each test in the folder (t)
    do
	testType=$(echo "$i" | cut -d/ -f4)
	testNum=$(echo "$t" | cut -d/ -f6)
        TestID="${testType}${testNum}";
        bin/mips_simulator "$t/binary.mips.bin";
        RESULT=$?;
	EXPECTATION=$(<"$t/expectation.txt");
        if [ "$RESULT" = "$EXPECTATION" ];
	then
            STATUS="Pass";
        else
            STATUS="Fail";
        fi
	AUTHOR_AND_MESSAGE=$(<"$t/about.txt");
	cs=", ";
        echo "${TestID}${cs}${testType}${cs}${STATUS}${cs}${AUTHOR_AND_MESSAGE}";
    done
    printf "\n=============================================================================\n";
done

