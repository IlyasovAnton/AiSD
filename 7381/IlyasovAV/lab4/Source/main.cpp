#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

#include "BTree.hpp"

#define TEST

int main() {
	std::string input_data;
	std::cout << "Enter the bracket tree view: ";
	std::getline(std::cin, input_data);
	input_data.erase(remove_if(input_data.begin(), input_data.end(), isspace), input_data.end());
	BinaryTree binary_tree(input_data);

	size_t depth = binary_tree.get_depth();
	std::cout << "The depth of this tree is equal to " << depth << std::endl;
	std::cout << std::endl;

	size_t path_length = binary_tree.get_path_length();
	std::cout << "the length of the path in this tree is equal to " << path_length << std::endl;
	std::cout << std::endl;

	binary_tree.print_leaves();
	std::cout << std::endl;

	int lvl;
	#ifndef TEST
		std::cout << "Enter a number between 1 and " << depth << ": ";
		std::cin >> lvl;
	#else
		srand(time(0));
		lvl = depth - rand() % depth;
	#endif
	size_t nodes_on_lvl = binary_tree.get_nodes_number(lvl);
	std::cout << "At level " << lvl << " is " << nodes_on_lvl << " nodes" << std::endl;
return 0;
}