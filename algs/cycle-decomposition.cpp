#include<iostream>
#include<vector>

using matrix = std::vector<std::vector<int>>;

matrix findCycleDecomposition(const std::vector<int>& permutation) {
	matrix toReturn;
	const size_t length = permutation.size();

	std::vector<bool> visited(length, false);
  
  // the if-nesting on row 14 could be avoided.
	for (size_t i = 0; i < length; i++) {
		if (!visited[i]) {
			visited[i] = true;
			if (permutation[i] != i + 1) {
				toReturn.push_back(std::vector<int>(1, i + 1));
				const size_t idx = toReturn.size() - 1;
				size_t k = permutation[i];

				while (k != i + 1) {
					visited[k - 1] = true;
					toReturn[idx].push_back(k);
					k = permutation[k - 1];
				}
			}
		}
	}

	return toReturn;
}

int main() {
	std::vector<int> permutation = { 3, 4, 5, 6, 1, 8, 7, 2, 9 };

	matrix result = findCycleDecomposition(permutation);

	for (size_t i = 0; i < result.size(); i++) {
		for (size_t j = 0; j < result[i].size(); j++) {
			std::cout << result[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
