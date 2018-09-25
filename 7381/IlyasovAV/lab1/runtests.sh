#!/bin/bash
echo -n > testsresult.txt

echo "Примеры корректных входных данных: "

echo "Тест1: 123.456"
echo "Тест 1: " >> testsresult.txt
./lab1 < Tests/test1.txt >> testsresult.txt

echo "Тест2: 123E456"
echo "Тест 2: " >> testsresult.txt
./lab1 < Tests/test2.txt >> testsresult.txt

echo "Тест3: 123.456E789"
echo "Тест 3: " >> testsresult.txt
./lab1 < Tests/test3.txt >> testsresult.txt

echo "Тест4: 1E+456"
echo "Тест 4: " >> testsresult.txt
./lab1 < Tests/test4.txt >> testsresult.txt

echo "Примеры некорректных входных данных: "

echo "Тест5: 123456"
echo "Тест 5: " >> testsresult.txt
./lab1 < Tests/test5.txt >> testsresult.txt

echo "Тест6: hello world"
echo "Тест 6: " >> testsresult.txt
./lab1 < Tests/test6.txt >> testsresult.txt

echo "Результаты тестов сохранены в файл testsresult.txt"
