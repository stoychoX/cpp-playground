// c++20 mergesort using stl functions
#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<span>
#include<cassert>

template
<class T, 
	template <class T> class container>
void mergeSort(container<T>& c) {
	if (c.size() < 2)
		return;

	size_t mid = c.size() / 2;

	container<T> left(c.begin(), c.begin() + mid);
	container<T> rigth(c.begin() + mid, c.end());

	mergeSort<T, container>(left);
	mergeSort<T, container>(rigth);

	std::merge(left.begin(), left.end(), rigth.begin(), rigth.end(), c.begin());
}

int main() {
	std::vector<int> v;
	
	for (size_t i = 0; i < 100; i++)
		v.push_back(rand() % 1000);

	mergeSort<int, std::vector>(v);
	assert(std::is_sorted(v.begin(), v.end()));

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(v.begin(), v.end(), g);
	assert(!std::is_sorted(v.begin(), v.end()));
	std::span<int> sp(v.begin(), v.end());					// less allocations that way

	mergeSort<int, std::span>(sp);
	assert(std::is_sorted(sp.begin(), sp.end()));
}
