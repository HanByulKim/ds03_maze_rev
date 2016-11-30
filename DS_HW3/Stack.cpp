#include "Stack.h"

Stack::Stack() {
	idx = 5;
	arr_x = new int[idx];
	arr_y = new int[idx];
}
Stack::~Stack() {
	delete[] arr_x;
	delete[] arr_y;
}

void Stack::array_doubling() {
	idx *= 2;
	int* temp = new int[size];
	for (int i = 0; i < size; i++)
		temp[i] = arr_x[i];
	delete arr_x;
	arr_x = new int[2 * size];
	for (int i = 0; i < size; i++)
		arr_x[i] = temp[i];

	for (int i = 0; i < size; i++)
		temp[i] = arr_y[i];
	delete arr_y;
	arr_y = new int[2 * size];
	for (int i = 0; i < size; i++)
		arr_y[i] = temp[i];
	delete[] temp;
}
void Stack::push(int nx, int ny) {
	if (idx == size) {
		array_doubling();
		std::cout << "sizeof " << idx << std::endl;
	}
	top++;
	arr_x[top] = nx;
	arr_y[top] = ny;
	size++;
}
void Stack::pop() {
	//std::cout << arr_x[top] << " " << arr_y[top] << std::endl;
	size--;
	top--;
}
int Stack::sizeis() { return size; }
int Stack::topx() { return arr_x[top]; }
int Stack::topy() { return arr_y[top]; }