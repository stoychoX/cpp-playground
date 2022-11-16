#include<iostream>
#include<string>
#include<vector>

using matrix = std::vector<std::vector<int>>;

int longestPalindromeSubseq(std::string s) {
	matrix fst(s.length(), std::vector<int>(s.length()));

	for (size_t i = 0; i < s.length(); i++) {
		for (size_t j = 0; j < s.length() - i; j++) {
			int start = j;
			int end = j + i;

			if (start == end) {
				fst[start][end] = 1;
			}
			else if(start + 1 == end) {
				fst[start][end] = 1 + (s[start] == s[end]);
			}
			else {
				if (s[start] == s[end]) {
					fst[start][end] = 2 + fst[start + 1][end - 1];
				}
				else {
					fst[start][end] = std::max(fst[start + 1][end], fst[start][end - 1]);
				}
			}
		}
	}
	return fst[0].back();
}


int main() {
	std::cout << longestPalindromeSubseq("abcde");
}
