#pragma once
class Stack {
public:
	Stack() {
		arr_x = new int[5];
		arr_y = new int[5];
	}

	void array_doubling() {
		int* temp = new int[size];
		for (int i = 0; i < size; i++)
			temp[i] = arr_x[i];
		delete arr_x;
		arr_x = new int[2 * size];
		for (int i = 0; i < size; i++)
			arr_x[i] = temp[i];
		delete temp;

		temp = new int[size];
		for (int i = 0; i < size; i++)
			temp[i] = arr_y[i];
		delete arr_y;
		arr_y = new int[2 * size];
		for (int i = 0; i < size; i++)
			arr_y[i] = temp[i];
		delete temp;
	}
	void push(int nx, int ny) {
		if ((sizeof(arr_x) / sizeof(*arr_x)) == size)
			array_doubling();
		arr_x[++top] = nx;
		arr_y[top] = ny;
		size++;
	}
	void pop() {
		size--;
		top--;
	}
	int sizeis() { return size; }
	int topx() { return arr_x[top]; }
	int topy() { return arr_y[top]; }

	int* arr_x;
	int* arr_y;
	int size = 0;
	int top = 0;
};