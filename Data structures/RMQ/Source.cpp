#include<iostream>
#include"RMQ.hpp"
#include<algorithm>
#include<thread>
#include<chrono>

struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Timer() {
		start = std::chrono::steady_clock::now();
	}

	~Timer() {
		end = std::chrono::steady_clock::now();
		duration = end - start;
		float output = duration.count() * 1.000f;
		std::cout << "executed for: " << output << " ms" << std::endl;
	}
};

int stl(size_t length) {
	std::vector<int> bigBoy;
	int res = 0;
	unsigned seed = time(0);

	for (size_t i = 0; i < length; i++)
		bigBoy.push_back(rand() % RAND_MAX);
	
	Timer t;
	for (size_t i = 0; i < length; i++) {
		for (size_t j = i; j < length; j++) {
			int fMin = *std::min_element(bigBoy.begin() + i, bigBoy.begin() + j + 1);
			res += fMin;
		}
	}
	return res;
}

int me(size_t length) {
	int res = 0;
	std::vector<int> bigBoy;

	for (size_t i = 0; i < length; i++)
		bigBoy.push_back(rand() % RAND_MAX);

	RMQ<int> rmq(bigBoy);

	Timer t;
	for (size_t i = 0; i < length; i++) {
		for (size_t j = i; j < length; j++) {
			int rmqMin = bigBoy[rmq.min(i, j)];
			res += rmqMin;
		}
	}
	return res;
}


void test(size_t length) {
	std::vector<int> bigBoy;

	unsigned seed = time(0);

	srand(seed);

	for (size_t i = 0; i < length; i++)
		bigBoy.push_back(rand() % RAND_MAX);

	RMQ<int> rmq(bigBoy);

	for (size_t i = 0; i < length; i++) {
		for (size_t j = i; j < length; j++) {
			int fMin = *std::min_element(bigBoy.begin() + i, bigBoy.begin() + j + 1);
			int rmqMin = bigBoy[rmq.min(i, j)];

			if (fMin != rmqMin) {
				std::cout << "ERR " << i << " " << j << std::endl;
			}
		}
	}

	std::cout << "Passed with seed: " << seed;
}

int main() {
	for (size_t i = (1 << 4); i <= (1 << 15); i <<= 1) {
		std::cout << i << std::endl;
		me(i);
		// stl(i);
	}

	for (size_t i = (1 << 4); i <= (1 << 10); i <<= 1) {
		test(i);
		std::cout << std::endl;
	}
}