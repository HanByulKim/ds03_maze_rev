#pragma once
#include <iostream>

class Node {
public:
	Node() {}
	Node(Node* h, int num) :header(h), n(num), next(NULL) {}
	Node(Node* h, int num, Node* ne) :header(h), n(num), next(ne) {}

	Node* header;
	int n;
	//int x, y;
	Node* next;
};