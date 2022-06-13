// Seen this task in my recent "design and analysis of algorithms" seminar.
// Solution with \Theta(n*(n+1)/2) memory complexity and O(n^2) time complexity.

#include<iostream>
#include<vector>

// Helper function to get from matrix indexing to array indexing.
int pairToIndex(size_t fst, size_t snd, size_t sizeOfMatrix) {
	if (snd < fst || fst >= sizeOfMatrix || snd >= sizeOfMatrix)
		return -1;

	int toReturn = fst;

	int diff = sizeOfMatrix - (snd - fst);

	int shift = sizeOfMatrix * (sizeOfMatrix + 1) / 2 - diff * (diff + 1) / 2;

	toReturn += shift;

	return toReturn;
}

// Word (l1)(b)(l2) is palindrome iff ((l1) == (l2)) && (b is palindrome).
// We know if b is palindrome as we have written it in our table.

// We need ((i + 1) < (j + 1)) check bc of corner cases like "aa"
// a == a, but we haven't got empty word as palindrome in our table, so we just return true.
int lengthOfBiggestPalindrome(const std::string& str) {
	size_t n = str.size();

	size_t cellsNeeded = n * (n + 1) / 2;

	std::vector<bool> table(cellsNeeded, false);

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n - i; j++) {
			int row = j;
			int col = j + i;

			bool res = false;

			if (row == col)
				res = true;
			else
				res = (str[row] == str[col]) && (!((row + 1) < (col - 1)) || table[pairToIndex(row + 1, col - 1, n)]);

			table[pairToIndex(row, col, n)] = res;
		}
	}

	int indexToReturn = 0;

	// Searching for the last 'true' -> this is the biggest palindrome.
	for (int i = cellsNeeded - 1; i >= 0; i--) {
		if (table[i]) {
			indexToReturn = i;
			break;
		}
	}

	++indexToReturn;

	// As we work with linear indexing we need to get the length of the palindrome only using the index
	// length is: 1 if idx \in [1..n]
	//			  2 if idx \in [n+1.. 2n - 1]
	//			  3 if idx \in [2n .. 3n - 2] etc

	// I couldn't come up with constant algorithm, so that will do the job.
	for (int i = n; i > 0; i--) {
		indexToReturn -= i;
		if (indexToReturn <= 0)
			return n - i + 1;
	}

	// Indicates mistake
	return -1;
}

int main() {
	std::string word = "addddddabcba"; // ans: 8 for adddddda
	std::cout << lengthOfBiggestPalindrome(word) << std::endl;

	word = "abababababababdddddddaaddddddd"; // ans: 16

	std::cout << lengthOfBiggestPalindrome(word);
}
