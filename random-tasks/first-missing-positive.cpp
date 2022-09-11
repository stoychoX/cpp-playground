// leetcode task to find the least positive number not contained in array in O(n) time & O(1) memory
#include<utility>
#include<vector>
#include<iostream>

class Solution {
public:
    int firstMissingPositive(std::vector<int> nums) {
        int result = INT_MAX;
        bool hasZero = false;

        for (size_t i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                hasZero = true;
                break;
            }
        }


        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] > 0 && nums[i] < nums.size() + !hasZero && nums[i] != i + !hasZero && nums[i] != nums[nums[i] - !hasZero]) {
                std::swap(nums[i], nums[nums[i] - !hasZero]);
            }
        }

        for (int i = hasZero; i < nums.size(); i++) {
            if (nums[i] != i + !hasZero) {
                result = i;
                break;
            }
        }

        if (result == INT_MAX)
            return nums.size() + !hasZero;
        return result + !hasZero;
    }
};

int main() {
    Solution s;
    std::cout <<  s.firstMissingPositive({ 0, -1, 3, 1 });
}
