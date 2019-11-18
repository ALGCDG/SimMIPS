#cleans .elf and .bins from test directories also containing .s files
for i in ./tests/*/
do
	for j in $i/*/
	do
		if [ -f $j/*.s ]; then
			rm $j/*.elf
			rm $j/*.bin
		fi
	done
done
