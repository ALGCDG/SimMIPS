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
cd tests;
for i in ls -d */
do
    cd $i
    for t in ls -d */
    do
        cd t;
        TestID = $i + $t;
        bin/mips_simulator binary.bin;
        RESULT = echo $?;
        EXPECTATION = cat expectation.txt;
        if $RESULT == $EXPECTATION;
        then
            STATUS = "Pass"
        else
            STATUS = "Fail"
        fi
        AUTHOR_AND_MESSAGE = cat about.txt
        echo ($TestID + ", " + $i + ", " + $STATUS + ", " + $AUTHOR_AND_MESSAGE)
        cd ..;
    done
    cd ..
done