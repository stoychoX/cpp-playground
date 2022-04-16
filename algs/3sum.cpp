int threeSumCount(std::vector<int> v, int elem) {
	std::sort(v.begin(), v.end());

	int res = 0;

	for (int i = 1; i < v.size() - 2; i++) {
		int start = i + 1;
		int end = v.size() - 2;

		while (start < end) {
			if (v[i] + v[start] + v[end] == elem) {
				++res;
				++start;
				--end;
			}
			else if (v[i] + v[start] + v[end] < elem) {
				start++;
			}
			else
				end--;
		}
	}
	return res;
}
