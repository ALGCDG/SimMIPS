#cleans .elf and .bins from test directories also containing .s files
for i in ./tests/*/
do
	for j in $i/*/
	do
		if [ -f $j/*.s ]; then
			rm -f $j/*.elf
			rm -f $j/*.bin
			rm -f $j/*.o
		fi
	done
done
