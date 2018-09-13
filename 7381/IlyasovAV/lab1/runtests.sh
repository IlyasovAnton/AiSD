echo -n > result.txt

echo "Test1 input: 123.456"
./lab1 < Tests/test1.txt

echo "Test2 input: 123E456"
./lab1 < Tests/test2.txt

echo "Test3 input: 123.456E789"
./lab1 < Tests/test3.txt

echo "Test4 input: 1E+456"
./lab1 < Tests/test4.txt

echo "Test5 input: 123456"
./lab1 < Tests/test5.txt

echo "Test6 input: hello world"
./lab1 < Tests/test6.txt