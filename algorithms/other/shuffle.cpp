#include<iostream>
#include<vector>
const int VECTOR_SIZE = 20;

// shuffle a vector to a random permutation.
// All permutations have equal possibility to occur.
void shuffle(std::vector<size_t>& v) {
	for(int i = 0; i < VECTOR_SIZE - 1; ++i) {
		size_t randomSwapIndex = rand() % (VECTOR_SIZE - i) + i;
		std::swap(v[i], v[randomSwapIndex]);
	}
}

void print(const std::vector<size_t>& v) {
	for(int i = 0; i < VECTOR_SIZE; ++i)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

int main() {
	std::vector<size_t> numbers;
	numbers.resize(VECTOR_SIZE);
  
	srand(time(NULL));
  
	for(int i = 0; i < VECTOR_SIZE; ++i)
		numbers[i] = rand() % 10000;

	print(numbers);
	shuffle(numbers);
	print(numbers);
}
