#pragma once
class Stack {
	Stack() {
		arr = new int[5];
	}

	void array_doubling() {
		int* temp = new int[size];
		for (int i = 0; i < size; i++)
			temp[i] = arr[i];
		delete arr;
		arr = new int[2 * size];
		for (int i = 0; i < size; i++)
			arr[i] = temp[i];
		delete temp;
	}
	void push(int n) {
		if ((sizeof(arr) / sizeof(*arr)) == size)
			array_doubling();
		arr[++top] = n;
		size++;
	}
	int pop() {
		size--;
		return arr[top--];
	}


	int* arr;
	int size = 0;
	int top = 0;
};