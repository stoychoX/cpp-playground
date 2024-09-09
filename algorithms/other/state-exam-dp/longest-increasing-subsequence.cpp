#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

// O(nlog(n)) algorithm solving LIS problem.
// https://www.dei.unipd.it/~geppo/DA2/DOCS/lis.pdf
void printLIS(const std::vector<int>& seq)
{
    // dp[k] at iteration j:
    // The last element of the longest increasing subsequence
    // with length k using elements {a_1, ..., a_j}
    // If there is more such sequences we mich the mininal such element.
    std::vector<int> dp(seq.size() + 1, INT_MAX);
    dp[0] = INT_MIN;
    dp[1] = seq[0];

    // index[i]:
    // The index in the original array of element at position i.
    std::vector<int> index(seq.size(), INT_MAX);
    index[1] = 0;

    // prev[i]:
    // The previous element in the sequence described by dp[i].
    std::vector<int> prev(seq.size(), INT_MAX);

    for (size_t i = 1; i < seq.size(); i++)
    {
        auto iter = std::lower_bound(
            dp.begin(),
            dp.end(),
            seq[i]
        );
        size_t idx = std::distance(dp.begin(), iter);

        dp[idx] = seq[i];
        index[idx] = i;
        prev[i] = index[idx - 1];
    }

    std::vector<int> result;
    
    auto lengthIt = std::lower_bound(dp.begin(), dp.end(), INT_MAX);
    size_t subsequenceIter = index[std::distance(dp.begin(), lengthIt) - 1];

    while(subsequenceIter != INT_MAX)
    {
        result.push_back(seq[subsequenceIter]);
        subsequenceIter = prev[subsequenceIter];
    }

    for(auto it = result.rbegin(); it != result.rend(); ++it)
    {
        std::cout << *it << ' ';
    }
}

int main()
{
    std::vector<int> mVect;

    srand(time(0));

    for (size_t i = 0; i < 10; i++)
        mVect.push_back(rand() % 100);

    for(auto x : mVect)
        std::cout << x << " ";
    
    std::cout << std::endl;

    printLIS(mVect);
}
