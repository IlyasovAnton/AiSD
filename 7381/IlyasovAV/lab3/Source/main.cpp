#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <algorithm>

#include "stack.hpp"

size_t priority(char operation);
bool is_operation (char symbol);
void infix_to_prefix(std::string &infix_data_notation, std::string &prefix_data_notation);

int main() {
	std::string infix_data_notation;
	std::string prefix_data_notation;

	std::getline(std::cin, infix_data_notation);			// Чтение происходит с потока ввода
	std::cout << "infix notation: " << infix_data_notation << std::endl;

	infix_data_notation.erase(remove_if(infix_data_notation.begin(), infix_data_notation.end(), isspace), infix_data_notation.end());
	infix_to_prefix(infix_data_notation, prefix_data_notation);

	std::cout << "result: " << prefix_data_notation << std::endl;			// Вывод происходит в поток вывода

	prefix_data_notation.clear();
	infix_data_notation.clear();
return 0;
}

size_t priority(char operation) {
	switch (operation) {
		case '+': case'-':
			return 1;
		case '*': case '/':
			return 2;
		case '^':
			return 3;
		default:
			return 0;
	}
}

bool is_operation (char symbol) {
	return (symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-') ? true : false;
}

void infix_to_prefix(std::string &infix_data_notation, std::string &prefix_data_notation) {
	Stack<char> stack;

	if (!isalpha(infix_data_notation[0]) && !isdigit(infix_data_notation[0]) && infix_data_notation[0] != '(') {
		std::cout << "--Error! At the beginning of the line expected '(', digit or letter, but was '" << infix_data_notation[0] << "'--" << std::endl;
		exit(0);
	}

	int index = infix_data_notation.length() - 1;
	if (!isalpha(infix_data_notation[index]) && !isdigit(infix_data_notation[index]) && infix_data_notation[index] != ')') {
		std::cout << "--Error! At the end of the line expected ')', digit or letter, but was '" << infix_data_notation[index] << "'--" << std::endl;
		exit(0);
	}

	while (index >= 0) {
		std::cout << "Current symbol - " << infix_data_notation[index] << ". Next step: ";
	// Обход строки производится в обратном порядке
		if (isalpha(infix_data_notation[index]) || isdigit(infix_data_notation[index])) {
			std::cout << "insert to output string" << std::endl;
			prefix_data_notation.insert(0, 1, infix_data_notation[index]);
			if (!isalpha(infix_data_notation[index-1]) && !isdigit(infix_data_notation[index-1]))
				prefix_data_notation.insert(0, 1, ' ');
			else {
				std::cout << "--Error! 2 variables in a row--" << std::endl;
				exit(0);
			}
		}
		else if (is_operation(infix_data_notation[index])) {
			if (is_operation(infix_data_notation[index-1])){
				std::cout << "--Error! 2 operators in a row--" << std::endl;
				exit(0);
			}
			if (!isalpha(infix_data_notation[index-1]) && !isdigit(infix_data_notation[index-1]) && infix_data_notation[index-1] != ')') {
				std::cout << "--Error! Expected ')', digit or letter, but was '" << infix_data_notation[index-1] << "'--" << std::endl;
				exit(0);
			}
			if (stack.empty()) {
				std::cout << "push to the stack" << std::endl;
				stack.push(infix_data_notation[index]);
				stack.print_stack();
			}
			else {
				std::cout << "work with stack" << std::endl;
				stack.print_stack();
				while (priority(infix_data_notation[index]) <= priority(stack.top()) && !stack.empty()) {
					std::cout << "\textract from stack and insert to output string '" << stack.top() << "'" << std::endl;
					prefix_data_notation.insert(0, 1, stack.top());
					stack.pop();
					stack.print_stack();
					prefix_data_notation.insert(0, 1, ' ');
				}
				std::cout << "\t'" << infix_data_notation[index] << "' push to the stack" << std::endl;
				stack.push(infix_data_notation[index]);
				stack.print_stack();
			}
		}
		else if (infix_data_notation[index] == ')') {
			if (is_operation(infix_data_notation[index-1])) {
				std::cout << "--Error! After ')' expected ')', digit or letter, but was '" << infix_data_notation[index-1] << "'--" << std::endl;
				exit(0);
			}
			std::cout << "push to the stack" << std::endl;
			stack.push(infix_data_notation[index]);
			stack.print_stack();
		}
		else if (infix_data_notation[index] == '(') {
			std::cout << "work with stack" << std::endl;
			stack.print_stack();
			while (priority(stack.top())) {
				std::cout << "\textract from stack and insert to output string '" << stack.top() << "'" << std::endl;
				prefix_data_notation.insert(0, 1, stack.top());
				stack.pop();
				stack.print_stack();
				prefix_data_notation.insert(0, 1, ' ');
			}
			if (stack.top() != ')') {
				std::cout << "--Error! Missing ')'--" << std::endl;
				exit(0);
			}
			stack.pop();
			stack.print_stack();
		}
		else {
			std::cout << "--Error! Extraneous symbol '" << infix_data_notation[index] << "'--" << std::endl;
			exit(0);
		}
		index--;
	}
	while (!stack.empty()) {
		if (stack.top() == ')') {
			// Если ) больше, чем (, то в стеке должны остаться лишние
			std::cout << "--Error! ')' more than '('--" << std::endl;
			exit(0);
		}
		prefix_data_notation.insert(0, 1, stack.top());
		stack.pop();
		prefix_data_notation.insert(0, 1, ' ');
	}
}