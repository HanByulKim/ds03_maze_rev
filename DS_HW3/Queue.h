#pragma once
class Queue {
public:
	Queue();
	~Queue();

	void array_doubling();
	void push(int nx, int ny);
	void pop();
	int sizeis();
	int frontx();
	int fronty();

private:
	int* arr_x;
	int* arr_y;
	int size = 0;
	int top = -1;
	int idx;
	int front = 0;
};