#!/bin/bash

if test ! -f "lab2"; then
	make
	clear
fi
if test -f "result.txt"; then
	rm result.txt 
fi

echo -n "Select the output method: 1 - on the screen; 2 - to the file: "
read output_method

if [[ $output_method == 1 || $output_method == 2 ]]; then
	echo -n "Enter abbreviated entry of the hierarchical list: "
	if test $output_method -eq 1; then
		./lab2
		exit
	fi
	if test $output_method -eq 2; then
		echo "result:" >> result.txt
		./lab2 >> result.txt
		echo "Result of the program is saved in result.txt"
		exit
	fi
else
	echo "Input error! Enter 1 or 2!"
	exit
fi