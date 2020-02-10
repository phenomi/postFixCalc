#pragma once
#include "Utility.h"
#include <iostream>

using namespace std;

const int maxstack = 50;   //  a rather small value (for testing purposes)

typedef float Stack_entry;

class Stack {
public:
	Stack();
	bool empty() const;
	bool full(Stack &s) const;
	int size(Stack &s) const;
	void instructions();
	char get_command();
	bool do_command(char command, Stack & numbers);
	void clear(Stack &s);
	void delete_all(Stack &s, Stack_entry x);
	Error_code pop();
	Error_code top(Stack_entry &item) const;
	Error_code push(const Stack_entry &item);
	Error_code copy_stack(Stack &dest, Stack&source);
	Error_code pop_top(Stack &s, Stack_entry &t);

private:
	int count;
	Stack_entry entry[maxstack];
};