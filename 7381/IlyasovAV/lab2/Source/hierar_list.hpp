#ifndef HIERAR_LIST_HPP
#define HIERAR_LIST_HPP

// описание структуры узла иерархического списка
	struct s_expr;
	struct two_ptr {
		s_expr *head;
		s_expr *tail;
	};

	struct s_expr {
		bool tag; // true: atom, false: pair
		union {
			char atom;
			two_ptr pair;
		} node;
	};
	typedef s_expr *lisp;
// базовые функции:
	lisp head(const lisp list);
	lisp tail(const lisp list);
	lisp cons(const lisp interim_list_1, const lisp interim_list_2);
	lisp make_atom(const char value);
	bool isAtom(const lisp list);
	bool isNull(const lisp list);
	char getAtom(const lisp list);
	void destroy(lisp list);
// функции ввода:
	void read_lisp(lisp& list);
	void read_s_expr(char prev, lisp &list);
	void read_seq(lisp &list);
// Функция подсчета глубины списка
	unsigned int list_depth_count(const lisp list, unsigned int counter);
#endif