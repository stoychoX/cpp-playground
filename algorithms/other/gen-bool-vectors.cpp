#include<iostream>
#include<vector>
#include<cassert>

using booleanVector = std::vector<bool>;
using booleanMatrix = std::vector<booleanVector>;

void update(booleanVector& v) {
	int i = v.size() - 1;
	while (v[i] && i) {
		v[i] = false;
		--i;
	}
	v[i] = true;
}

booleanMatrix allVectors(unsigned n) {
	assert(n != 0 && n < 33);

	booleanVector item(n, false);

	booleanMatrix result;

	size_t length = (1 << n); // 2^n

	result.resize(length);

	for (size_t i = 0; i < length; i++) {
		result[i] = item;
		update(item);
	}

	return result;
}

void print(const booleanVector& v) {
	for (bool x : v)
		std::cout << x << " ";
	std::cout << std::endl;
}

int main() {
	booleanMatrix res = allVectors(17);
	for (const auto& v : res)
		print(v);
}
