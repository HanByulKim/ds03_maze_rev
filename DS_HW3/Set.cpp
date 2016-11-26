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
		std::cout << itr->n << " " << std::endl;
	}
}

void Set::union_set(Set& unirand) {

}