#pragma once
#include <iostream>
class Stack {
public:
	Stack();
	~Stack();

	void array_doubling();
	void push(int nx, int ny);
	void pop();
	int sizeis();
	int topx();
	int topy();

	int* arr_x;
	int* arr_y;
	int size = 0;
	int top = -1;
	int idx;
};