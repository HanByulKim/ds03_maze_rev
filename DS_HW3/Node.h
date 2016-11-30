#pragma once
#include <iostream>

class Node {
public:
	Node() {}
	Node(Node* h, int num) :header(h), n(num), next(NULL) {}
	Node(Node* h, int num, int leb) :header(h), n(num), next(NULL), leben(leb) {}
	Node(Node* h, int num, Node* ne) :header(h), n(num), next(ne) {}

	Node* header;
	int n;
	//int x, y;
	bool l = 1, r = 1, t = 1, b = 1;
	int leben;
	Node* next;
};