#pragma once
#include "Node.h"

class Set {
public:
	Set() {
		head = new Node();
		tail = head;
	};
	~Set() {
		init(0);
	}

	void init(int num);
	void setunioned(int a);
	void add(int idx);
	void print();
	int getsize();
	int unionedchk();
	void union_set(Set& unirand);

	Node* head;
	Node* tail;
	int unioned;
	int size = 0;
};