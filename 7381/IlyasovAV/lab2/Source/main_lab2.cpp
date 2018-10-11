#include <iostream>
#include <cstdlib>

#include "hierar_list.hpp"

int main() {
	lisp list;
	read_lisp(list);
	if (isNull(list))
		std::cout << "List is empty or was not created" << std::endl;
	else {
		std::cout << "The depth of this hierarchical list is " << list_depth_count(list, 0) << "." << std::endl;
		destroy(list);
	}
return 0;
}