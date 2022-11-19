// https://leetcode.com/problems/container-with-most-water/
#include<vector>

int maxArea(const std::vector<int>& height) {
	size_t startIndex = 0;
	size_t endIndex = height.size() - 1;

	int result = INT_MIN;

	while (startIndex < endIndex) {
		int currentHeigth = std::min(height[startIndex], height[endIndex]) * (endIndex - startIndex);

		result = std::max(result, currentHeigth);

		if (height[startIndex] > height[endIndex]) {
			--endIndex;
		}
		else {
			++startIndex;
		}
	}

	return result;
}
