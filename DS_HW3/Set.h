#pragma once
#include "Node.h"

class Set {
public:
	Set() {
		head = new Node();
		tail = head;
	};

	void add(int idx);
	void print();
	void union_set(Set& unirand);

private:
	Node* head;
	Node* tail;
	int size = 0;
};