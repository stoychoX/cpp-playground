#include<iostream>
#include<vector>
#include<string>

// Kinda ugly but thats not the point here
void printBinary(int n) {
    bool metOne = false;

    for (int i = 31; i >= 0; i--) {
        int powerOfTwo = 1 << i;

        if (metOne == false)
            metOne = ((n & powerOfTwo) != 0);

        if (metOne)
            std::cout << ((n & powerOfTwo) != 0);
    }

    if (!metOne) std::cout << "0";
    
    std::cout << std::endl;
}

// Input: string containing 0, 1 and *
// Output replace all stars with 0 and 1

// Example:
//
// In: 1*1
// Out: 101, 111
void allBinary(const std::string& data) {
    size_t length = data.size();
    std::vector<size_t> starsIndexes;
    size_t result = 0;

    for (int i = 0; i < length; ++i) {
        result += (1 << (length - i - 1)) * (data[i] == '1');

        if (data[i] == '*')
            starsIndexes.push_back((length - i - 1));
    }

    std::vector<size_t> nums;

    for (int i = starsIndexes.size() - 1; i >= 0; --i) {
        size_t local = static_cast<size_t>(1) << starsIndexes[i];
        size_t end = nums.size();
        for (size_t i = 0; i < end; i++)
            nums.push_back(nums[i] + local);
        nums.push_back(local);
    }

    printBinary(result);

    for (size_t x : nums)
        printBinary(result + x);
}

int main() {
    //allBinary("*001*110");
    allBinary("1**1");
    // allBinary("1001*1");
}
