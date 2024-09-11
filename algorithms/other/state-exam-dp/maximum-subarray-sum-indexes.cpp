#include <iostream>
#include <climits>
#include <vector>

using IndexPair = std::pair<unsigned, unsigned>;

// Kadane's algorithm modified to find the indexes
// of the maximum sum array.
IndexPair maxSum(const std::vector<int> &v)
{
    int current_sum = 0;
    int best_sum = INT_MIN;

    int start = -1;
    int end = -1;

    int current_start = 0;

    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] > current_sum + v[i])
        {
            current_start = i;
            current_sum = v[i];
        }
        else
        {
            current_sum = current_sum + v[i];
        }

        if (current_sum > best_sum)
        {
            start = current_start;
            end = i;
            best_sum = current_sum;
        }
    }

    return {start, end};
}

int main()
{
    std::vector<int> example = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    auto result = maxSum(example);
    std::cout << result.first << " " << result.second;
}
