// Seen this task's solution from: https://www.youtube.com/watch?v=LPFhl65R7ww

#include<vector>

double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
	if (nums1.size() > nums2.size())
		std::swap(nums1, nums2);

	int n = nums1.size();           // shorter array
	int m = nums2.size();           // longer array

	int l = 0;
	int h = nums1.size();       // bsearch on the shorter one!

	while (l <= h) {
		int partitionX = (l + h) / 2;
		int partitionY = (n + m + 1) / 2 - partitionX;

		int leftMaxX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
		int rigthMinX = (partitionX == n) ? INT_MAX : nums1[partitionX];

		int leftMaxY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
		int rigthMinY = (partitionY == m) ? INT_MAX : nums2[partitionY];

		if (leftMaxX <= rigthMinY && leftMaxY <= rigthMinX) {
			if ((m + n) % 2 == 0)
				return (double)(std::max(leftMaxX, leftMaxY) + std::min(rigthMinY, rigthMinX)) / 2.0;

			return (double)std::max(leftMaxX, leftMaxY);
		}
		else if (leftMaxX > rigthMinY) {
			h = partitionX - 1;
		}
		else {
			l = partitionX + 1;
		}
	}
	return 0;
}
