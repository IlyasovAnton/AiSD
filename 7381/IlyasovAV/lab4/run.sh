#!/bin/bash

if test ! -f "lab4"; then
	make
	make clean
fi

clear
./lab4

make clean