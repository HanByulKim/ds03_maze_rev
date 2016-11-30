#include "Set.h"

void Set::add(int idx) {
	Node* a = new Node(head, idx);
	tail->next = a;
	tail = tail->next;
	size++;
}

void Set::print() {
	Node* itr = head;
	for (int i = 0; i < size; i++) {
		itr = itr->next;
		std::cout << itr->n << " ";
	}
	std::cout << std::endl;
}

void Set::union_set(Set& unirand) {
	int cri = unirand.getsize();
	Node* itr = unirand.head;
	for (int i = 0; i < cri; i++) {
		itr = itr->next;
		add(itr->n);
	}
	unirand.init(head->next->n);
}

int Set::getsize() { return size; }
int Set::unionedchk() { return unioned; }

void Set::init(int num) {
	int d = size;
	for (int i = 0; i < d; i++) {
		delete tail;
		size--;
		tail = head;
		for (int j = 0; j < size; j++) {
			tail = tail->next;
		}
	}

	head = NULL;
	tail = NULL;
	size = 0;
}

void Set::setunioned(int a) {
	unioned = a;
}