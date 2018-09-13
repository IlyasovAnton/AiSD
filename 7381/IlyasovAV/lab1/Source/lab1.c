#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void tabs(int deepCount) {									// Функция печати отступов
	for (int i = 0; i < deepCount; i++)
		printf(".\t");
}

int isDigit(char symbol, int deepCount) {

	tabs(deepCount);
	printf("Вызов функции isDigit для %c:\n", symbol);

	int interimResult = isdigit(symbol);

	tabs(deepCount+1);
	printf(interimResult ? "Это цифра!\n" : "Это не цифра!\n");
	tabs(deepCount);
	printf("Завершение функции isDigit для %c.\n", symbol);

	return interimResult;
}

int isUnsignedInteger(char *string, int deepCount) {

	tabs(deepCount);
	printf("Вызов функции isUnsignedInteger для %s:\n", string);

	int interimResult = 1;
	char *interimString = string;
	if (strlen(string) == 1) {								// Если строка представляет собой один символ
		char symbol = string[0];
		interimResult = isDigit(symbol, deepCount+1);
	}
	else {											// Если строка состоит из нескольких символов
		interimString = string;
		char symbol = string[0];
		string = string + 1;
		interimResult = isDigit(symbol, deepCount+1) && isUnsignedInteger(string, deepCount+1);
	}
	tabs(deepCount);
	printf("Завершение функции isUnsignedInteger для %s: ", interimString);
	printf(interimResult ? "Это целое без знака!\n" : "Это не целое без знака!\n");

	return interimResult;
}

int isInteger(char *string, int deepCount) {

	tabs(deepCount);
	printf("Вызов функции isInteger для %s:\n", string);
	
	int interimResult = 1;
	char *interimString = string;
	if (string[0] == '+')
		string = string + 1;

	if (!strlen(string)) {
		interimResult = 0;
	}
	else {
		interimResult = isUnsignedInteger(string, deepCount+1);
	}

	tabs(deepCount);
	printf("Завершение функции isInteger для %s: ", interimString);
	printf(interimResult ? "Это целое число!\n" : "Это не целое число!\n");

	return interimResult;
}

void isRealNumber(char *string) {

	printf("\nВызов функции isRealNumber для %s:\n", string);

	int result = 1;
	char *firstPart;									// Указатели
	char *secondPart;									// под части строки,
	char *thirdPart;									// потенциально представляющие целое или целое без знака

	if (strchr(string, '.')) {
		char *delimiter = strchr(string, '.');						//
		firstPart = string;								//
		secondPart = delimiter+1;							//
		*delimiter = '\0';								//

		if (!isInteger(firstPart, 1)) {
			result = 0;
		}
		else if (strchr(secondPart, 'E')) {
			char *delimiter = strchr(secondPart, 'E');				//
			thirdPart = delimiter+1;						// При обнаружении символов '.' или 'Е'
			*delimiter = '\0';							// разделаем строку, заменяя эти символы на '\0'
			result = isInteger(secondPart, 1) && isInteger(thirdPart, 1);		//
		}
		else {
			result = isInteger(secondPart, 1);
		}

	}
	else if (strchr(string, 'E')) {
		char *delimiter = strchr(string, 'E');						//
		firstPart = string;								//
		secondPart = delimiter+1;							//
		*delimiter = '\0';								//
		result = isInteger(firstPart, 1) && isInteger(secondPart, 1);
	}
	else {											// В противном случае строка
		result = 0;									// не удовлетворяет заданному условию
	}
	
	printf("Завершение функции isRealNumber, результат: ");
	printf(result ? "Это вещественное число!\n" : "Это не вещественное число!\n");
}

int main() {
	setlocale(LC_ALL, "Russian");
	char *input_data = malloc(sizeof(char) * 200);
	fgets(input_data, 20, stdin);
	if (input_data[strlen(input_data) - 1] == '\n')
		input_data[strlen(input_data) - 1] = '\0';

	freopen("result.txt", "a+", stdout); 							// Перенаправление потока вывода в файл
	isRealNumber(input_data);
	fclose (stdout); 									// Закрытие потока вывода
	
	free(input_data);
	return 0;
}