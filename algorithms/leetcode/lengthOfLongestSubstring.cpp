#include<iostream>
#include<string>
#include<map>

int lengthOfLongestSubstring(const std::string& s) {
        std::map<char, size_t> lastPos;
        size_t pos = 0;
        size_t ans = 0;

        for (size_t i = 0; i < s.length(); i++) {
            bool contains = !(lastPos.count(s[i]) == 0);

            size_t lastPosOfChar = lastPos[s[i]];

            if (contains && lastPosOfChar >= pos) {
                ans = std::max(ans, i - pos);
                pos = lastPosOfChar + 1;
            }

            lastPos[s[i]] = i;

        }

        ans = std::max(ans, s.length() - pos);

        return ans;
}

int main() {
    std::cout << lengthOfLongestSubstring("dvdf");
}
