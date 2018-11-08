#!/bin/bash

if test ! -f "infix.txt"; then
	echo "Infix.txt not found"
	exit
fi
if test -f "prefix.txt"; then
	rm prefix.txt
fi
touch prefix.txt

if test ! -f "lab3"; then
	g++ ./Source/main.cpp -o lab3
fi
echo -n "Select the input method: 1 - from the keyboard; 2 - from the infix.txt: "
read input_method
echo -n "Select the output method: 1 - to the keyboard; 2 - to the prefix.txt: "
read output_method

if [[ $input_method == 1 || $input_method == 2 && $output_method == 1 || $output_method == 2 ]]; then
	if test $input_method -eq 1; then
		echo -n "enter infix expression: "
		if test $output_method -eq 1; then
			./lab3
		else
			./lab3 >> prefix.txt
			echo "Result of the program is saved in prefix.txt"
		fi
		exit
	fi
	if test $input_method -eq 2; then
		if test $output_method -eq 1; then
			./lab3 < infix.txt
		else
			./lab3 < infix.txt >> prefix.txt
			echo "Result of the program is saved in prefix.txt"
		fi
		exit
	fi
else
	echo "Input error! Enter 1 or 2!"
	exit
fi

echo "The expression is translated in the prefix form and written in the prefix.txt"