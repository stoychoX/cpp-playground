#include<iostream>
#include<vector>
#include<exception>

int maxSubarraySum(const std::vector<int>& v) {
  if (v.empty()) throw std::exception("Empty vector passed as argument");

	int cSum = v[0];
	int mSum = v[0];

	for (int i = 1; i < v.size(); i++) {
		if (cSum > 0)
			cSum += v[i];
		else
			cSum = v[i];
		if (cSum > mSum)
			mSum = cSum;
	}
	return mSum;
}
