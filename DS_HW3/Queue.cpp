#include "Queue.h"
#include <iostream>

Queue::Queue() {
	idx = 5;
	arr_x = new int[idx];
	arr_y = new int[idx];
}
Queue::~Queue() {
	delete[] arr_x;
	delete[] arr_y;
}

void Queue::array_doubling() {
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
void Queue::push(int nx, int ny) {
	if (idx == size) {
		array_doubling();
	}
	top++;
	arr_x[top] = nx;
	arr_y[top] = ny;
	size++;
}
void Queue::pop() {
	front++;
}
int Queue::sizeis() { return size; }
int Queue::frontx() { return arr_x[front]; }
int Queue::fronty() { return arr_y[front]; }