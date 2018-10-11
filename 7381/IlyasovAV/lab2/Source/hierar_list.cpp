#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include "hierar_list.hpp"

// базовые функции:
lisp head(const lisp list) {
	if (list) {
		if (!isAtom(list))
			return list->node.pair.head;
		else {
			std::cout << "--Error: Head(atom)--" << std::endl;
			exit(0);
		}
	}
	else {
		std::cout << "--Error: Head(nil)--" << std::endl;
		exit(0);
	}
}

lisp tail(const lisp list) {
	if (list) {
		if (!isAtom(list))
			return list->node.pair.tail;
		else {
			std::cout << "--Error: Tail(atom)--" << std::endl;
			exit(0);
		}
	}
	else {
		std::cout << "--Error: Tail(nil)--" << std::endl;
		exit(0);
	}
}

lisp cons(const lisp interim_list_1, const lisp interim_list_2) {
	lisp list;
	if (isAtom(interim_list_2)) {
		std::cout << "--Error: Cons(*, atom)--" << std::endl;
		exit(0);
	}
	else {
		list = new s_expr;
		if (!list) {
			std::cout << "--Memory not enough--" << std::endl;
			exit(0);
		}
		else {
			list->tag = false;
			list->node.pair.head = interim_list_1;
			list->node.pair.tail = interim_list_2;
			return list;
		}
	}
}

lisp make_atom(const char value) {
	lisp list = new s_expr;
	list->tag = true;
	list->node.atom = value;
	return list;
}

bool isAtom(const lisp list) {
	return list ? list->tag : false;
}

bool isNull(const lisp list) {
	return !list;
}

char getAtom(const lisp list) {
	if (!isAtom(list)) {
		std::cout << "--Error: getAtom(!atom)--" << std::endl;
		exit(0);
	}
	else
		return list->node.atom;
}

void destroy(lisp list) {
	if (list) {
		if (!isAtom(list)) {
			destroy(head(list));
			destroy(tail(list));
		}
	delete list;
	}
}
// функции ввода:
void read_lisp(lisp &list) {
	char x;
	do std::cin >> x; while (x == ' ');
	read_s_expr(x, list);
}

void read_s_expr(char prev, lisp &list) {
	if (prev == ')') {
		std::cout << "--Error: unexpected ')'--" << std::endl;
		exit(0);
	}
	else if (prev != '(')
		list = make_atom(prev);
	else 
		read_seq(list);
}

void read_seq(lisp &list) {
	char x;
	lisp p1, p2;
	if (!(std::cin >> x)) {
		std::cout << "--Error: data entry expected--" << std::endl;
		exit(0);
	}
	else {
		while (x == ' ') std::cin >> x;
		if (x == ')')
			list = NULL;
		else {
			read_s_expr(x, p1);
			read_seq(p2);
			list = cons(p1, p2);
		}
	}
}
// Функция подсчета глубины списка
unsigned int list_depth_count(const lisp list, unsigned int counter) {
	unsigned int max_depth_count = 1;
	unsigned int depth_count = 0;

	if (isNull(list) || isAtom(list))							// Глубина пустого списка и глубина
		return 0;									// атомарного S-выражения равны нулю

	for (lisp viewed = list; viewed; viewed = viewed->node.pair.tail) {
		if (!isNull(viewed)) {
			depth_count++;
			if (!isAtom(viewed)) {

				if (isAtom(head(viewed))) {					// выражение
					for (int i = 0; i < counter; i++)			// для
						std::cout << "\t";				// вывода
					std::cout << head(viewed)->node.atom << std::endl;	// промежуточного
				}								// результата,
				else {								// демонстрирующего
					for (int i = 0; i < counter; i++) 			// визуализацию
						std::cout << "\t";				// уровней
					std::cout << "------->" << std::endl;			// вложенности
				}								// списка
				
				depth_count += list_depth_count(viewed->node.pair.head, counter+1);
			}
			else {
				return 1;
			}
		}
		else {
			return 0;
		}

		if (depth_count > max_depth_count)						// выбор максимальной
			max_depth_count = depth_count;						// глубины вложенности
		
		depth_count = 0;
	}
return max_depth_count;
}