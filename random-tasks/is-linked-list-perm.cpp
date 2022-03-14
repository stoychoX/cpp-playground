#include<iostream>
#include<stack>

struct linkedList {
	int data;
	linkedList* next;

	linkedList(int d, linkedList* n = nullptr) : data(d), next(n) {}
};

// Solution inspired by cppnuts: 
// https://www.youtube.com/watch?v=s6GAAml3Z0M&t
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

// my iterative approach
bool checkIfPalindromeIterative(const linkedList* l) {
	std::stack<const linkedList*> s;

	s.push(l);
	int size = 0;

	while (s.top()) {
		s.push(s.top()->next); 
		++size;
	}

	int mid = size / 2;
	s.pop();
	for (int i = 0; i < mid; i++) {
		if (l->data != s.top()->data)
			return false;

		s.pop();
		l = l->next;
	}

	return true;

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
				new linkedList(4,
					new linkedList(3, 
						new linkedList(2,
							new linkedList (1)))))));

	std::cout << checkIfPalindromeIterative(pal);

	freeLinkedList(pal);
}
