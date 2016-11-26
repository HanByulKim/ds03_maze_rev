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
	int getsize();
	void union_set(Set& unirand);

	Node* head;
	Node* tail;
	int size = 0;
};