// We define Excellent Pair as: (a, b) => popcount(a & b) + popcount(a | b) >= k 
// for some constant k

// Find all Excellent Pair in given array and constant k.

// (3, 3) is a valid pair and its Excellent Pair for k = 3.
// (2, 3) and (3, 2) are different pairs.

// Solved in O(nlog(n)) time (std::sort + some linear iterations) and O(n) space (std::set used for makeUnique)

// hint: popcount(a & b) + popcount(a | b) = popcount(a) + popcount(b) (Why?)
// Then we just sort all unique popcounts and do modified 2sum 
#include<vector>
#include<set>
#include<algorithm>

class Solution {
private:
	void makeUnique(std::vector<int>& v) {
		    std::set<int> s(v.begin(), v.end());
        v.assign(s.begin(), s.end());
   }

	int popcount(unsigned int v) {
		int res = 0;
		
    for (int i = 0; i < 32; i++)
			res += (v & (1 << i)) != 0;
    
		return res;
	}

public:
	long long countExcellentPairs(std::vector<int>& nums, int k) {
		makeUnique(nums);
    
		long long res = 0;
		
    for (size_t i = 0; i < nums.size(); i++) {
			nums[i] = popcount(nums[i]);
			res += ((2 * nums[i]) >= k);                   // Counting pairs of type (a, a)
		}

    std::sort(nums.begin(), nums.end());
        
		int l = 0;
		int h = nums.size() - 1;
		while (l < h) {
			int cSum = nums[l] + nums[h];

			if (cSum >= k) {
				res += 2 * (h - l);
				h--;
			}
			else
				l++;
		}

		return res;
	}
};
