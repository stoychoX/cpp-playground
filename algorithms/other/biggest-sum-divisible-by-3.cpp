#include <iostream>
#include <algorithm>
#include <vector>

// O(n) dynamic programming approach for finding the biggest sum
// in array divisible by 3.
unsigned findMaxSum(const std::vector<unsigned>& numbers)
{
    unsigned sumModuloOne = 0;
    unsigned sumModuloTwo = 0;
    unsigned answer = 0;

    for (size_t i = 0; i < numbers.size(); i++)
    {
        if((answer + numbers[i]) % 3 == 0)
        {
            answer += numbers[i];
            sumModuloOne += numbers[i];
            sumModuloTwo += numbers[i];
        }
        else if(numbers[i] % 3 == 1)
        {
            unsigned oldAns = answer;

            if(sumModuloTwo != 0)
            {
                answer = std::max(sumModuloTwo + numbers[i], answer);
            }
            
            if(sumModuloOne != 0)
            {
                sumModuloTwo = std::max(sumModuloOne + numbers[i], sumModuloTwo);
                sumModuloOne = std::max(oldAns + numbers[i], sumModuloOne);
            }

            if(sumModuloOne == 0)
            {
                sumModuloOne = numbers[i];
            }
        }
        else
        {
            unsigned oldSumModOne = sumModuloOne;

            if(sumModuloTwo != 0)
            {
                sumModuloOne = std::max(sumModuloOne, numbers[i] + sumModuloTwo);
                sumModuloTwo = std::max(numbers[i] + answer, sumModuloTwo);
            }

            if(sumModuloOne != 0)
            {
                answer = std::max(oldSumModOne + numbers[i], answer);
            }

            if(sumModuloTwo == 0)
            {
                sumModuloTwo = numbers[i];
            }
        }

        std::cout << "[" << numbers[i] << "]:" << sumModuloOne << " " << sumModuloTwo << " " << answer << std::endl;
    }

    return answer;
}

int main()
{
    std::vector<unsigned> example = {4, 15, 9, 17, 4, 3, 2, 4, 5, 1};

    std::cout << findMaxSum(example);
}
