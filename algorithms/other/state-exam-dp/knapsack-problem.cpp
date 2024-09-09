#include <iostream>
#include <vector>
#include <fstream>

void printTable(int** table, int x, int y, std::ofstream& outFile) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
			outFile << table[i][j] << ',';
		outFile << std::endl;
	}

	outFile << std::endl;
}

int knapsack(const std::vector<int>& weights, const std::vector<int>& values, const int W) {
	std::ofstream outFile("result.csv");

	const int n = weights.size();

	int** table = new int* [n + 1];

	for (int i = 0; i < n + 1; i++)
		table[i] = new int[W + 1];

	for (int i = 0; i < n+1; i++)
		table[i][0] = 0;

	for (int i = 0; i < W + 1; i++)
		table[0][i] = 0;

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < W + 1; j++) {
			if (weights[i - 1] > j)
				table[i][j] = table[i - 1][j];
			else
				table[i][j] = std::max(table[i - 1][j], values[i - 1] + table[i - 1][j - weights[i - 1]]);
			printTable(table, n + 1, W + 1, outFile);
		}	
	}

	int res = table[n][W];

	for (int i = 0; i < n + 1; i++)
		delete[] table[i];

	delete[] table;
	return res;
}

int main() {
	std::cout << knapsack({ 10, 20, 30 }, { 60, 100, 120 }, 50);
}
