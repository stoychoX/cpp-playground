#include<iostream>
#include<string>
#include<map>

int lengthOfLongestSubstring(const std::string& s) {
    std::map<char, int> m;
    size_t globalMax = 0;
    int beg = 0;

    for(int i = 0; i < s.size(); ++i) {
        if(m[s[i]] > 0) {
            if(m.size() > globalMax)
                globalMax = m.size();
            
            while(m[s[i]] > 0)
                m.erase(s[beg++]);
        }
        m[s[i]] = 1;
    }
    
    return std::max(m.size(), globalMax);
}

int main() {
    std::cout << lengthOfLongestSubstring("dvdf");
}
