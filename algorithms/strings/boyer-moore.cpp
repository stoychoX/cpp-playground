#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<fstream>

#define APLHABET_SIZE CHAR_MAX

struct pattern {
	std::string pat;

	std::vector<size_t> badChar;
	std::vector<size_t> goodSuffix;
};

void initGoodSuffix(const std::string& str, std::vector<size_t>& arg) {
	arg.resize(str.size() + 1, 0);
	std::vector<size_t> bpos(str.size() + 1, 0);

	int currentChar = str.length();

	int beg = str.length() + 1;

	bpos[currentChar] = beg;

	while(currentChar > 0) {
		while(beg <= str.length() && str[currentChar - 1] != str[beg - 1]) {
			if(arg[beg] == 0)
				arg[beg] = beg - currentChar;

			beg = bpos[beg];
		}

		currentChar--;
		beg--;
		bpos[currentChar] = beg;
	}

	int j = bpos[0];

	for (size_t i = 0; i < str.size(); i++) {
		if(arg[i] == 0)
			arg[i] = j;
		
		if(i == j)
			j = bpos[j];
	}
}

void initBadChar(const std::string& str, std::vector<size_t>& arg) {
	arg.resize(APLHABET_SIZE, str.length());

	for (size_t i = 0; i < str.length(); i++)
		arg[str[i]] = str.length() - i - 1;
}

void initPattern(const std::string& str, pattern& arg) {
	arg.pat = str;
	initBadChar(str, arg.badChar);
	initGoodSuffix(str, arg.goodSuffix);
}

void printTables(const pattern& arg) {
	std::cout << "Bad char: " << std::endl; 
	for(auto x : arg.badChar)
		std::cout << x << " ";

	std::cout << std::endl;
	std::cout << "Good suffix: " << std::endl; 

	for(auto x : arg.goodSuffix)
		std::cout << x << " ";
	std::cout << std::endl;
}

void search(const std::string& str, const pattern& arg) {
	int indexPosition = arg.pat.size() - 1;

	while(indexPosition < str.length()) {
		int indexString = indexPosition;
		int indexPattern = arg.pat.size() - 1;

		while(indexPattern >= 0 && str[indexString] == arg.pat[indexPattern]) {
			--indexPattern;
			--indexString;
		}

		if(indexPattern < 0) {
            // cout in search just for the demo.
			std::cout << "Matched at " << indexPosition - arg.pat.length() + 1 << std::endl;
			indexPosition += arg.goodSuffix[0];
		}
		else {
			indexPosition += std::max(arg.badChar[str[indexString]], arg.goodSuffix[indexPattern + 1]);
		}
	}
}

int main() {
	std::string text = "This is some text where we search given pattern. Write pattern second time.";
    pattern p;
    initPattern("pattern",p);
    search(text, p);
}