#include<iostream>  
#include<vector>
#include<string>

std::string getLongestPalindrome(const std::string& str) {
    if(str.empty())
        return "";
  
    // true ако подниза [i][j] е палиндром false в противен случай
    std::vector<std::vector<bool>> isPalindrome(str.size(), std::vector<bool>(str.size(), false));

    int resStrat = 0;
    int resEnd = 0;

    // Всички поднизове [i][i] са палиндроми.
    for (size_t i = 0; i < str.size(); i++)
        isPalindrome[i][i] = true;
    
    // [i][i+1] е палиндром когато str[i] == str[i+1]
    for (size_t i = 0; i < str.size() - 1; i++){
        isPalindrome[i][i+1] = (str[i] == str[i+1]);

        if(isPalindrome[i][i+1]) {
            resStrat = i;
            resEnd = i + 1;
        }
    }

    // [i][j + i] е палиндом когато str[i]==str[i + j] и когато този помежду им е палиндром
    // j e начален индекс, i е offset.
    for (size_t i = 2; i < str.size(); i++) {
        for (size_t j = 0; j < str.size() - i + 1; j++){ 
            isPalindrome[j][j + i] = (str[j] == str[j + i]) && isPalindrome[j + 1][j + i - 1];

            // Понеже индексите стават все по - "отдалечени" последния палиндром винаги ще е най - дълъг
            if(isPalindrome[j][j + i]) {
                resStrat = j;
                resEnd = j + i;
            }
        }
    }
    
    return std::string (str.begin() + resStrat, str.begin() + resEnd + 1);
}

int main() {
    std::cout << getLongestPalindrome("alabbabobbobracrd");
}
