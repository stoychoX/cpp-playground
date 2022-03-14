#include<iostream>

struct linkedList {
	int data;
	linkedList* next;

	linkedList(int d, linkedList* n = nullptr) : data(d), next(n) {}
};

bool checkIfPalindromeRecursive(const linkedList*& left, const linkedList* rigth) {
	if (rigth == nullptr)
		return true;
	bool p = checkIfPalindromeRecursive(left, rigth->next) && (rigth->data == left->data);

	left = left->next;

	return p;
}

bool checkIfPalindrome(const linkedList* l) {
	return checkIfPalindromeRecursive(l, l);
}

void freeLinkedList(linkedList* toDel) {
	if (toDel == nullptr)
		return;
	linkedList* c = toDel;
	freeLinkedList(toDel->next);
	delete toDel;
}

int main() {
	linkedList* pal = new linkedList(1,
		new linkedList(2,
			new linkedList(3,
				new linkedList(2,
					new linkedList(1)))));

	std::cout << checkIfPalindrome(pal);

	freeLinkedList(pal);
}
