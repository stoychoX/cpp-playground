#include<iostream>

struct LinkedListNode {
	int data;
	LinkedListNode* next;

	LinkedListNode(int d, LinkedListNode* n = nullptr) :
		data(d), next(n) {}
};

LinkedListNode* init(std::initializer_list<int> il) {
	if (il.size() == 0) return nullptr;

	LinkedListNode* toReturn = new LinkedListNode(*il.begin());
	LinkedListNode* last = toReturn;

	auto it = il.begin();
	++it;

	for (; it != il.end(); ++it) {
		last->next = new LinkedListNode(*it);
		last = last->next;
	}
	return toReturn;
}

void printNode(const LinkedListNode* ll) {
	const LinkedListNode* it = ll;

	while (it) {
		std::cout << it->data << " ";
		it = it->next;
	}
	std::cout << std::endl;
}

void freeNode(LinkedListNode* ll) {
	while (ll) {
		LinkedListNode* c = ll;
		ll = ll->next;
		delete c;
	}
}

// Reverse returns new reversed linked list (iterative)
LinkedListNode* reverse(const LinkedListNode* ll) {
	if (ll == nullptr)
		return nullptr;

	LinkedListNode* it = ll->next;
	LinkedListNode* toReturn = new LinkedListNode(ll->data);

	while (it) {
		LinkedListNode* putMeFirst = new LinkedListNode(it->data);

		putMeFirst->next = toReturn;
		toReturn = putMeFirst;

		it = it->next;
	}

	return toReturn;
}

// reverse list with O(1) additional memory (recursive)
void reverseListHelper(LinkedListNode* ll, LinkedListNode*& last, LinkedListNode*& result) {
	if (ll->next == nullptr) {
		last = ll;
		result = last;
		return;
	}
	reverseListHelper(ll->next, last, result);
	
	ll->next = nullptr;
	last->next = ll;
	last = last->next;
}

void reverseList(LinkedListNode*& ll) {
	if (ll == nullptr)
		return;

	LinkedListNode* last = nullptr;
	LinkedListNode* result = nullptr;

	reverseListHelper(ll, last, result);
	ll = result;
}

int main() {
	LinkedListNode* example = init({ 6, 9, 14, 4, 1, 12, 9, 6, 5, 2, 18, 15 });
	std::cout << "Original list: " << std::endl;
	printNode(example);
	LinkedListNode* reversed = reverse(example);
	reverseList(example);
	printNode(example);
	printNode(reversed);
	
	freeNode(example);
	freeNode(reversed);
}
