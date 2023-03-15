// Quick sort with only one recursive call
// c++20 needed
#include<iostream>
#include<vector>
#include<span>
#include<cassert>
#include<algorithm>

size_t partition(std::span<int>& s) {
	int pivot = s.back();
	size_t pp = 0;

	for (int i = 0; i < s.size() - 1; i++)
		if (s[i] < pivot)
			std::swap(s[i], s[pp++]);

	std::swap(s[s.size() - 1], s[pp]);
  
	return pp;
}

void qsort(std::span<int>& arg, size_t lo, size_t hi) {
	while (lo < hi) {
		size_t at = partition(arg);
		std::span<int> left(arg.begin(), at);
		qsort(left, 0, at);
		lo += at + 1;
		arg = arg.subspan(at + 1);
	}
}

void qsort(std::vector<int>& arg) {
	std::span<int> s(arg.begin(), arg.size());
	qsort(s, 0, arg.size() - 1);
}

int main() {
	std::vector<int> v;

	for (size_t i = 0; i < 1000; i++)
		v.push_back(rand());

	qsort(v);
	assert(std::is_sorted(v.begin(), v.end()));
}
