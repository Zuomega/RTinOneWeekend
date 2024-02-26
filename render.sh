FILE=./img.ppm
if test -f "$FILE"; then
	echo "$FILE exists."
	rm img.ppm 
	echo "The old $FILE removed."
fi
./a.out >> img.ppm
