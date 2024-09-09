#include <iostream>
#include <vector>
#include <climits>

template<class T>
void display(const T& v)
{
    for(const auto& r : v)
    {
        for(const auto& val : r)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl; 
    }
    std::cout << std::endl; 

    std::cin.get();
}

unsigned lcseq(const std::string& str1, const std::string& str2)
{
    std::vector<std::vector<unsigned>> dp(
        str1.size() + 1, 
        std::vector<unsigned>(str2.size() + 1, 0));
    
    for (size_t i = 1; i <= str1.size(); i++)
    {
        for (size_t j = 1; j <= str2.size(); j++)
        {
            if(str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }

            // display(dp);
        }
    }
    
    return dp[str1.size()][str2.size()];
}

int main()
{
    std::string str1 = "hello";
    std::string str2 =  "_h___ e  l _ l___";
    std::cout << lcseq(str1, str2);
}
