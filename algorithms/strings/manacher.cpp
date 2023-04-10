#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

std::string manacher(const std::string& str, char sep = '|', char beg = '$', char end = '#') {
	if (str.empty()) {
		return "";
	}

	std::string mString = "";

	for (char c : str) {
		mString += sep;
		mString += c;
	}

	mString += sep;

	size_t length = mString.length();

	mString = beg + mString + end;

	std::vector<size_t> halfIndex(length, 0);
	size_t center = 0;
	size_t right = 0;

	for (size_t i = 1; i < length; i++) {
		if (i < right) {
			size_t symethric = 2 * center - i;
			halfIndex[i] = std::min(right - i, halfIndex[symethric]);
		}

		while (mString[i - halfIndex[i] - 1] == mString[i + halfIndex[i] + 1]) {
			++halfIndex[i];
		}

		if (i + halfIndex[i] > right) {
			center = i;
			right = i + halfIndex[i];
		}
	}

	std::vector<size_t>::iterator maxVal = std::max_element(halfIndex.begin(), halfIndex.end());
	size_t mIdx = std::distance(halfIndex.begin(), maxVal);

	std::string::iterator from = mString.begin() + mIdx - halfIndex[mIdx];
	std::string::iterator to = mString.begin() + mIdx + halfIndex[mIdx] + 1;

	std::string toReturn;
	std::copy_if(
		from,
		to,
		std::back_inserter(toReturn),
		[&](char c) -> bool {
			return c != sep;
		}
	);

	return toReturn;
}

int main() {
	std::cout << manacher("abracadabra");
}
