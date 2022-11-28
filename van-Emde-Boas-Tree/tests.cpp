#include<iostream>
#include<cassert>
#include<algorithm>
#include"vEBTree.h"

/*
g++ -std=c++20 -O0 .\tests.cpp .\vEBTree.cpp 

Or enable c++20 on visual studio.
*/

void tests() {
	auto size = 1LL << 20;
	vEBTree t(size);
	std::vector<unsigned long long> v;
	v.resize(10000);

	for (size_t i = 0; i < 10000; i++) {
		v[i] = rand() % size;
		t.insert(v[i]);
	}

	for (auto x : v) { assert(t.find(x)); }

	t.remove(v[0]);
	assert(!t.find(v[0]));

	size_t idx = rand() % v.size();
	t.remove(v[idx]);
	assert(!t.find(v[idx]));

	std::vector<unsigned long long> vs;
	int sz = t.size();
	while (!t.empty()) {
		vs.push_back(t.min());
		t.remove(t.min());
	}

	assert(std::is_sorted(vs.begin(), vs.end()));

	assert(vs.size() == sz);

	for (size_t i = 0; i < 100; i++) {
		t.insert(i);
		t.insert(i + 300);
	}
	for (size_t i = 0; i < 100; i++) {
		assert(t.pred(i) == i); 
		assert(t.succ(i) == i);
	}

	for (size_t i = 100; i < 300; i++) {
		assert(t.pred(i) == 99);
		assert(t.succ(i) == 300);
	}

	assert(t.pred(500) == 399);

	std::cout << "All good";
}

int main() {
	tests();
}