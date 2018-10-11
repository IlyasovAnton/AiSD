#!/bin/bash 

if test ! -f "lab2" ; then
	make
	clear
fi
if test -f "testsresult.txt"; then
	rm testsresult.txt 
fi

touch testsresult.txt

for i in $(ls ./Tests/correct); do
	echo "running correct $i: $(cat Tests/correct/$i | more)"
		sleep 0.1s
	echo "correct test: "$i"" >> testsresult.txt
	echo "test data: $(cat Tests/correct/$i | more)" >> testsresult.txt
	echo "result: " >> testsresult.txt
	./lab2 < ./Tests/correct/$i >> testsresult.txt
	echo -e >> testsresult.txt
	echo "###################################################" >> testsresult.txt
done
for i in $(ls ./Tests/incorrect); do
	echo "running incorrect $i: $(cat Tests/incorrect/$i | more)"
		sleep 0.1s
	echo "incorrect test: "$i"" >> testsresult.txt
	echo "test data: $(cat Tests/incorrect/$i | more)" >> testsresult.txt
	echo "result: " >> testsresult.txt
	./lab2 < ./Tests/incorrect/$i >> testsresult.txt
	echo -e >> testsresult.txt
	echo "###################################################" >> testsresult.txt
done

sleep 0.2s
echo -e
echo  "test results are saved in testsresult.txt"