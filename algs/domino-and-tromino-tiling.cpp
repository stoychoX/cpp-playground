// https://leetcode.com/problems/domino-and-tromino-tiling/solutions/2947522/c-dynamic-programming-0ms-6-5-mb-solution-with-explanation/

#include<iostream>
#include<vector>

class Solution {
public:
	int numTilings(int n) {
		if (n < 3)
			return n;

		std::vector<size_t> dp(n + 1, 0);
		dp[0] = 0;
		dp[1] = 1;
		dp[2] = 2;

		int accumulate = 2;

		for (size_t i = 3; i <= n; i++) {
			dp[i] = (dp[i - 1] + dp[i - 2] + accumulate) % (int)(1e9 + 7);
			accumulate += 2 * dp[i - 2];
		}

		return dp[n];
	}
};

int main() {
	Solution s;

	std::cout << s.numTilings(7);
}
