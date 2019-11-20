cd ./mips_testbench/tests
a=0
j=0
for i in ./*/
do
	for k in $i/*/
	do
		if [[ $(<$k/about.txt) == *"Jonathan,"* ]];
		then
			j=$((j+1))
		elif [[ $(<$k/about.txt) == *"Archie,"* ]];
		then
			a=$((a+1))
		fi
	done
done
echo $a
echo $j
