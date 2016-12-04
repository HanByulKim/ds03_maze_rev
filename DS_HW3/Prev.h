#pragma once
class Prev {
public:
	Prev() { x = 0; y = 0; }
	void designate(int a, int b) {
		x = a;
		y = b;
	}
	int getx() { return x; }
	int gety() { return y; }
	
private:
	int x;
	int y;
};