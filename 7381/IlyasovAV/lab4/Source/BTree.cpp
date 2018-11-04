#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cmath>

#include "BTree.hpp"

#define TEST

void print_tabs(size_t tabs) {
	for (size_t count = 0; count < tabs; count++)
		std::cout << ".\t";
}

BinaryTree::BinaryTree() {
	left = NULL;
	root = NULL;
	right = NULL;
}

BinaryTree::BinaryTree(std::string &string) {
	read__binary_tree(string);
}

void BinaryTree::read__binary_tree(std::string &string) {
	if (string[0] == '(' && string[string.length()-1] == ')') {
		string = string.substr(1, string.length()-2);
		record_to_root(string[0]);
		string = string.substr(1, string.length()-1);

		if (!string.length())
			return;

		if (string[0] == '(') {
			size_t index = 0;
			size_t brackets_count = 0;
			do {
				if (string[index] == '(')
					brackets_count++;
				if (string[index] == ')')
					brackets_count--;
				index++;
			} while (brackets_count > 0);
			std::string substring_left = string.substr(0, index);
			create_tree_branches(substring_left, LEFT);
			string = string.substr(index);
		}
		else if (string[0] == '#') {
			string = string.substr(1, string.length()-1);
		}
		else {
			std::cout << "--Error! Expected brackets or '#', but was '" << string[0] << "'--" << std::endl;
			exit(0);
		}

		if (string.length() == 0)
			return;

		if (string[0] == '(') {
			create_tree_branches(string, RIGHT);
		}
		else if (string[0] == '#') {
			string = string.substr(1, string.length()-1);
		}
		else {
			std::cout << "--Error! Expected brackets or '#', but was '" << string[0] << "'--" << std::endl;
			exit(0);
		}
	}
	else {
		std::cout << "--Error! Tree elements must be enclosed in parentheses--" << std::endl;
		exit(0);
	}
}

void BinaryTree::record_to_root(char value) {
	if (isdigit(value) || isalpha(value)) {
		this->value = value;
		left = NULL;
		right = NULL;
	}
	else {
		std::cout << "--Error! Invalid character '" << value << "'--" << std::endl;
		exit(0);
	}
}

void BinaryTree::create_tree_branches(std::string &string, side_t side) {
	if (side == LEFT) {
		left = new BinaryTree();
		left->root = this;
		left->read__binary_tree(string);
	}
	else {
		right = new BinaryTree();
		right->root = this;
		right->read__binary_tree(string);
	}
}

size_t BinaryTree::get_depth() {
	#ifndef TEST
		std::cout << "Call depth calculation method" << std::endl;
	#endif
	size_t depth = get_depth(1);
	this->depth = depth;
	return depth;
}

size_t BinaryTree::get_depth(size_t lvl) {
	#ifndef TEST
		print_tabs(lvl);
		std::cout << "method call. Current root - " << value << ". Current depth is " << lvl << std::endl;
	#endif
	size_t left_depth = 1;
	size_t right_depth = 1;
	if (left) left_depth += left->get_depth(lvl+1);
	if (right) right_depth += right->get_depth(lvl+1);
	// каждый раз выбирается максимальная глубина поддеревьев
	size_t max_depth = std::max(left_depth, right_depth);
	#ifndef TEST
		print_tabs(lvl);
		std::cout << "exit method. compare the depth of the subtrees: left = " << left_depth-1 << ", right = " << right_depth-1
		<< ". Choose more, that is " << max_depth-1 << std::endl;
	#endif
	return max_depth;
}

size_t BinaryTree::get_path_length() {
	#ifndef TEST
		std::cout << "Call the method of calculating the length of the path in this tree" << std::endl;
	#endif
	return get_path_length(1);
}

size_t BinaryTree::get_path_length(size_t lvl) {
	#ifndef TEST
		print_tabs(lvl);
		std::cout << "method call. Current root - " << value << std::endl;
	#endif
	if (!left && !right) {
		#ifndef TEST
			print_tabs(lvl);
			std::cout << "exit method. It's a leave" << std::endl;
		#endif
		return 0;
	}
	else {
		size_t left_length = 0;
		size_t right_length = 0;
		if (left) left_length += 1 + left->get_path_length(lvl+1);
		if (right) right_length += 1 + right->get_path_length(lvl+1);
		size_t length = left_length + right_length;
		#ifndef TEST
			print_tabs(lvl);
			std::cout << "exit method. look at the length of the subtree paths: left = " << left_length << ", right = " << right_length
			<< ". total path is " << left_length << " + " << right_length << " = " << length << std::endl;
		#endif
		return length;
	}
}

void BinaryTree::print_leaves() {
	std::string leaves = "";
	#ifndef TEST
		std::cout << "Call the method of printing the leaves of this tree" << std::endl;
	#endif
	print_leaves(1, leaves);
	std::cout << "All the leaves of this tree: " << leaves << std::endl;
}

void BinaryTree::print_leaves(size_t lvl, std::string &leaves) {
	#ifndef TEST
		print_tabs(lvl);
		std::cout << "method call. Current root - " << value << std::endl;
	#endif
	if (!left && !right) {
		#ifndef TEST
			print_tabs(lvl);
			std::cout << "exit method. It's a leave" << std::endl;
		#endif
		leaves += value;
		leaves += " ";
	}
	else {
		if (left) left->print_leaves(lvl+1, leaves);
		if (right) right->print_leaves(lvl+1, leaves);
		#ifndef TEST
			print_tabs(lvl);
			std::cout << "exit method. look at the leaves found: " << leaves << std::endl;
		#endif
	}
}

size_t BinaryTree::get_nodes_number(int depth_lvl) {
	if (depth_lvl < 1) {
		std::cout << "--Error! Expected number not less than 1--" << std::endl;
		exit(0);
	}
	if (depth_lvl > depth) {
	// аргумент не должен превышать максимальную глубину дерева
		std::cout << "--Error! The argument entered is greater than the tree depth--" << std::endl;
		exit(0);
	}
	#ifndef TEST
		std::cout << "Call the method that counts the number of nodes at a given level" << std::endl;
	#endif
	return get_nodes_number(depth_lvl, 1);
}

size_t BinaryTree::get_nodes_number(int depth_lvl, size_t lvl) {
	#ifndef TEST
		print_tabs(lvl);
		std::cout << "method call. Current lvl is " << lvl << std::endl;
	#endif
	if (depth_lvl == 1) {		
	// необходимый уровень достигается, когда lvl уменьшается до 1
		#ifndef TEST
			print_tabs(lvl);
			std::cout << "exit method. reached the desired level" << std::endl;
		#endif
		return 1;
	}
	else {
		size_t nodes_number = 0;
		if (left) nodes_number += left->get_nodes_number(depth_lvl-1, lvl+1);
		if (right) nodes_number += right->get_nodes_number(depth_lvl-1, lvl+1);
		#ifndef TEST
			print_tabs(lvl);
			std::cout << "exit method. found " << nodes_number << " nodes" << std::endl;
		#endif
		return nodes_number;
	}
}

BinaryTree::~BinaryTree() {
	if (left)
		delete left;
	if (right)
		delete right;
}