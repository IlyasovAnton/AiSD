#ifndef __BTREE_HPP__
#define __BTREE_HPP__

enum side_t {LEFT, RIGHT};

class BinaryTree {
private:
	char value;								// Переменная для хранения значения в корне
	size_t depth;							// Переменная для хранения глубины дерева
	BinaryTree *left;
	BinaryTree *root;
	BinaryTree *right;
	void read__binary_tree(std::string &string);					// Методы четния
	void record_to_root(char value);								// входной строки и 
	void create_tree_branches(std::string &string, side_t side);	// создания дерева

	size_t get_depth(size_t lvl);
	size_t get_path_length(size_t lvl);
	void print_leaves(size_t lvl, std::string &leaves);
	size_t get_nodes_number(int depth_lvl, size_t lvl);
public:
	BinaryTree();
	BinaryTree(std::string &string);

	size_t get_depth();											// Метод для пункта а)
	size_t get_path_length();									// Метод для пункта б)
	void print_leaves();										// Метод для пункта в)
	size_t get_nodes_number(int depth_lvl);						// Метод для пункта г)

	~BinaryTree();
};

#endif