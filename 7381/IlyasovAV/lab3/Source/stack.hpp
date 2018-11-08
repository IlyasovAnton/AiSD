#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <cstddef>

template <class Type>
class Stack {
	private:
		size_t _top;
		size_t _size;
		Type *_data;
	public:
		Stack();

		Type top();
		void pop();
		void push(const Type &value);
    
		size_t size() const;
		bool empty() const;
		void print_stack();

		~Stack();
};

template <class Type>
Stack<Type>::Stack() {
	_top = 0;
	_size = 1;
	_data = new Type[_size];
}

template <class Type>
Type Stack<Type>::top() {
	if (empty()) {
		std::cout << "Error! Stack is empty" << std::endl;
		exit(0);
	}
	return _data[_top - 1];
}

template <class Type>
void Stack<Type>::pop() {
	--_top;
}

template <class Type>
void Stack<Type>::push(const Type &value) {
	_data[_top] = value;
	++_top;

	if (_top == _size) {
		size_t new_size = _size * 2;
		Type *new_data = new Type[new_size];
		for (size_t index = 0; index < _size; index++)
			new_data[index] = _data[index];
		delete[] _data;
		_size = new_size;
		_data = new_data;
	}
}

template <class Type>
size_t Stack<Type>::size() const {
	return _top;
}

template <class Type>
bool Stack<Type>::empty() const {
	return !_top;
}

template <class Type>
void Stack<Type>::print_stack() {
	std::cout << "\tStack:  ";
	if (empty())
		std::cout << "Stack is empty";
	else
		for (int index = _top-1; index >= 0; index--)
			std::cout << _data[index] << " ";
	std::cout << std::endl;
}

template <class Type>
Stack<Type>::~Stack() {
	delete[] _data;
}

#endif