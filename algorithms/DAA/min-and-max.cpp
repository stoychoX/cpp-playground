
// Standard algo for min & max makes 2n-2 comparisons
// here we make just ceil(3n/2)
template<class T>
std::pair<T, T> minAndMaxElement(const std::vector<T>& v) {
	if (v.size() < 2)
		throw std::exception("Vector is too small");

	int minElementIndex;
	int maxElementIndex;

	bool smaller = (v[0] < v[1]);

	minElementIndex = !smaller;
	maxElementIndex = smaller;

	for (size_t i = 2; i < v.size() - 1; i += 2) {
		bool isFirstSmaller = v[i] < v[i + 1];

		int smallerIndex = isFirstSmaller ? i : i + 1;
		int biggerIndex = isFirstSmaller ? i + 1 : i;

		if (v[smallerIndex] < v[minElementIndex]) minElementIndex = smallerIndex;
		if (v[biggerIndex] > v[maxElementIndex]) maxElementIndex = biggerIndex;
	}

	if (v.size() % 2 == 1) {
		if (v.back() < v[minElementIndex]) minElementIndex = v.size() - 1;
		if (v.back() > v[maxElementIndex]) maxElementIndex = v.size() - 1;
	}

	return { v[minElementIndex], v[maxElementIndex] };
}
// still std::min_element + std::max_element is faster though.
