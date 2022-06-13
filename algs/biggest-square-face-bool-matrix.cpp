#include<iostream>
#include<vector>

// Input: boolean matrix
// Output: face of the biggest square containing only 1s

int faceOfBiggestSquare(const std::vector<std::vector<bool>>& v) {
	if (v.empty())
		return 0;

	size_t n = v[0].size();
	size_t m = v.size();

	int toReturn = 0;

	std::vector<std::vector<int>> table(m, std::vector<int>(n, 0));

	for (size_t i = 0; i < n; i++)
		table[0][i] = v[0][i];

	for (size_t i = 1; i < m; i++) {
		table[i][0] = v[i][0];

		for (size_t j = 1; j < n; j++) {
			if (v[i][j] == 0)
				table[i][j] = 0;
			else
				table[i][j] = 1 + std::min(table[i][j - 1], std::min(table[i - 1][j], table[i - 1][j - 1]));

			toReturn = std::max(toReturn, table[i][j]);
		}
	}

	return toReturn * toReturn;
}

int main() {
	std::vector<std::vector<bool>> example = {
		{1, 1, 0, 1, 0, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1}
	}; // ans: 16

	std::vector<std::vector<bool>> exampleTwo = {
		{1, 1, 0, 1, 0, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 1, 0, 0, 1},
		{0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1}
	}; // ans: 4

	std::vector<std::vector<bool>> exampleThree = {
		{1, 1, 0},
		{1, 0, 0},
		{0, 0, 0},
		{1, 0, 1}
	}; // ans: 1

	std::cout << 
    faceOfBiggestSquare(example) << std::endl <<
		faceOfBiggestSquare(exampleTwo) << std::endl <<
		faceOfBiggestSquare(exampleThree);
}
