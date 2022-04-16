int partition(std::vector<int>& v) {
	int pp = 0;
	int pivot = v[v.size() - 1];

	std::cout << pivot << std::endl;

	for (int i = 0; i < v.size() - 1; i++)
		if (v[i] < pivot)
			std::swap(v[i], v[pp++]);

	std::swap(v[pp], v[v.size() - 1]);

	return pp;
}
