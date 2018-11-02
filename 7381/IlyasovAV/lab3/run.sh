#!/bin/bash

if test ! -f "infix.txt"; then
	echo "Infix.txt not found"
	exit
fi
if test -f "prefix.txt"; then
	rm prefix.txt
fi

touch prefix.txt

g++ ./Source/main.cpp -o lab3
./lab3

echo "The expression is translated in the prefix form and written in the prefix.txt"

rm lab3