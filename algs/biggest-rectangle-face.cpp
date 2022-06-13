#include<iostream>
#include<vector>
#include<stack>

/// <summary>
///Example:
///   *
///  **   -> In this case the max face is 4.
/// ***
///____
/// </summary>
/// <param name="hist">Vector representing histogram</param>
/// <returns>Max face of rectangle in histogram</returns>
int maxRectangleAreaHistogram(const std::vector<int>& hist) {
	int maxArea = 0;
	std::stack<int> s;

	s.push(0);

	int n = hist.size();

	std::vector<int> temp(n + 2);
	
	temp[0] = 0;
	
	for (size_t i = 0; i < n; ++i)
		temp[i + 1] = hist[i];
	
	temp[n + 1] = 0;

	for (size_t i = 1; i < n + 2; i++) {
		while (temp[i] < temp[s.top()]) {
			int cVal = s.top();
			s.pop();
			int cArea = temp[cVal] * (i - s.top() - 1);
			maxArea = std::max(maxArea, cArea);
		}
		s.push(i);
	}
	return maxArea;
}

/// <summary>
/// I've seen this algorithm and "biggest-square face" in one my "design and analysis of algorithms" seminars.
/// </summary>
/// <param name="v">Boolean matrix</param>
/// <returns>Biggest face of rectangle containing only ones.</returns>
int faceOfBiggestRectangle(const std::vector<std::vector<bool>>& v) {
	if (v.empty())
		return 0;

	int m = v.size();
	int n = v[0].size();

	std::vector<int> hist(n);

	int toReturn = 0;

	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			if (v[i][j])
				hist[j]++;
			else
				hist[j] = 0;
		}

		toReturn = std::max(toReturn, maxRectangleAreaHistogram(hist));
	}
	return toReturn;
}

int main() {
	std::vector<std::vector<bool>> example = {
		{1, 1, 0, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1}
	}; // ans: 20

	std::vector<std::vector<bool>> exampleTwo = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 0, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1}
	}; // and: 9

	std::vector<std::vector<bool>> exampleThree = {
		{1, 1, 0},
		{1, 0, 0},
		{0, 0, 0},
		{1, 0, 1}
	}; // ans: 2

	std::cout << faceOfBiggestRectangle(example) << std::endl <<
				 faceOfBiggestRectangle(exampleTwo) << std::endl <<
				 faceOfBiggestRectangle(exampleThree);
}
