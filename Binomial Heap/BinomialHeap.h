#ifndef BINOMIAL_HEAP_HEADER
#define BINOMIAL_HEAP_HEADER
#include"BinomialTree.h"
#include<vector>

class BinomialHeap {
	std::vector<BinomialTree> data;
public:
	BinomialHeap();
	BinomialHeap(int);
	
	void merge(BinomialHeap&);
	void insert(int elem);

	int getMin() const;
	int extractMin();

	bool empty() const;
	void flush();
};
#endif