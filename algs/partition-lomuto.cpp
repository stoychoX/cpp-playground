int partition(std::vector<int>& v) {
	int pp = 0;
	int pivot = v[v.size() - 1];

	for (int i = 0; i < v.size() - 1; i++)
		if (v[i] < pivot)
			std::swap(v[i], v[pp++]);

	std::swap(v[pp], v[v.size() - 1]);

	return pp;
}
