#!/bin/bash

echo "Running testbench..."

# testing return codes
# file should be csv and have fields, input binary, purpose of test (which instruction we are testing), expected output code, author
tests = $( cat test_file.csv )
file | grep -o "hello,"

cat filename | while read LINE; do
    echo $LINE
done
# testing character outputs