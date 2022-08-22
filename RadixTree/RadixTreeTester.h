#ifndef RADIX_TREE_TESTER
#define RADIX_TREE_TESTER

#include"RadixTree.h"
#include<cassert>
#include<fstream>
#include<string>
#include<vector>
#include<iostream>

class RadixTreeTester {
private:
	void correctChildrenTests() {
		RadixTree<AlphabetType::ASCII> trie;
		std::ifstream inFile("huge-file.txt");
		std::cout << "Start loading words in tree\n";
		while (!inFile.eof()) {
			std::string str;
			inFile >> str;
			trie.insert(str);
		}
		std::cout << "Loading finished. Start checking children count..\n";
		recChildrenTest(trie.root);
		std::cout << "Count check finished\n";
	}

	void recChildrenTest(RadixTree<AlphabetType::ASCII>::Node* r) {
		uint16_t c = 0;
		for (size_t i = 1; i < r->data.size(); i++) {
			c += (bool)(r->data[i]);
			if (r->data[i])
				recChildrenTest(r->data[i]);
		}
		assert(c == r->children);
	}

	void insertionAndSearchTestFirst() {
		RadixTree<AlphabetType::ASCII> trie;
		std::ifstream inFile("huge-file.txt");
		std::vector<std::string> v;

		std::cout << "Start loading words in tree and in vector\n";

		while (!inFile.eof()) {
			std::string str;
			inFile >> str;
			trie.insert(str);
			v.push_back(str);
		}
		std::cout << "Finished loading start searching for every word\n";


		for (size_t i = 0; i < v.size(); i++)
			assert(trie.search(v[i]));
		std::cout << "Finished searching\n";
	}

	void insertionAndSearchTestSecond() {
		RadixTree<AlphabetType::ASCII> trie;
		std::ifstream inFile("huge-file.txt");
		std::vector<std::string> v;

		std::cout << "Start loading unique words in vector\n";

		while (!inFile.eof()) {
			std::string str;
			inFile >> str;
			if (std::find(v.begin(), v.end(), str) == v.end())
				v.push_back(str);
		}
		std::cout << "Finished loading words in vector start inserting...\n";

		size_t length = v.size() / 2;

		for (size_t i = 0; i < length; i++)
			trie.insert(v[i]);


		std::cout << "Start searching (words in)...\n";

		for (size_t i = 0; i < length; i++)
			assert(trie.search(v[i]));
		
		std::cout << "Start searching (words out)...\n";

		for (size_t i = length; i < v.size(); i++)
			assert(!trie.search(v[i]));

		std::cout << "Finished searching\n";
	}

	void removalTestFirst() {
		RadixTree<AlphabetType::ASCII> trie;
		std::ifstream inFile("huge-file.txt");
		std::vector<std::string> v;

		std::cout << "Start loading unique words in vector\n";

		while (!inFile.eof()) {
			std::string str;
			inFile >> str;
			if (std::find(v.begin(), v.end(), str) == v.end())
				v.push_back(str);
		}
		std::cout << "Finished loading words in vector start inserting...\n";

		for (size_t i = 0; i < v.size(); i++)
			trie.insert(v[i]);
		std::cout << "Inserted unique words in vector. start removing and checking...\n";

		for (size_t i = 0; i < v.size(); i++) {
			assert(trie.search(v[i]));
			assert(trie.remove(v[i]));
			assert(!trie.remove(v[i]));
			assert(!trie.search(v[i]));
			recChildrenTest(trie.root);
		}
	}
public:
	void runTests() {
		insertionAndSearchTestFirst();
		insertionAndSearchTestSecond();
		correctChildrenTests();
		removalTestFirst();
		std::cout << "Test are successful!\n";
	}
};

#endif // !RADIX_TREE_TESTER