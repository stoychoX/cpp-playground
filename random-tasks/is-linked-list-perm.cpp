#include<iostream>
#include<stack>
#include<thread>
#include<chrono>

struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Timer() {
		start = std::chrono::steady_clock::now();
	}

	~Timer() {
		end = std::chrono::steady_clock::now();
		duration = end - start;
		float output = duration.count() * 1.000f;
		std::cout << "executed for: " << output << " ms" << std::endl;
	}
};

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
	linkedList* pal = new linkedList(0);
	linkedList* curr = pal;

	for (int i = 1; i < 5000; i++) {
		curr->next = new linkedList(i);
		curr = curr->next;
	}

	{
		std::cout << "Check if big list is palindrome with iterative approach: " << std::endl;
		Timer t;
		std::cout << checkIfPalindromeIterative(pal);
		std::cout << std::endl;
	}

	{
		std::cout << "Check if big list is palindrome with recursive approach: " << std::endl;
		Timer t;
		std::cout << checkIfPalindrome(pal);
		std::cout << std::endl;
	}

	freeLinkedList(pal);
}
