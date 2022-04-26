#include "BinomialTree.h"
#include <limits.h>

void BinomialTree::free(Node*& r) {
	if (r == nullptr)
		return;

	free(r->rightSibling);
	free(r->leftChild);

	delete r;
}

int BinomialTree::getData(const Node const* r) {
	if (r)
		return r->data;
	return INT_MAX;
}

BinomialTree::BinomialTree() {
	root = nullptr;
	rank = static_cast<size_t>(-1);
}

BinomialTree::BinomialTree(int data) {
	rank = 0;
	this->root = new Node(data);
}

BinomialTree::BinomialTree(BinomialTree&& other) {
	this->root = other.root;
	other.root = nullptr;

	this->rank = other.rank;
	other.rank = static_cast<size_t>(-1);
}

BinomialTree& BinomialTree::operator=(BinomialTree&& other) {
	if (this != &other) {
		this->root = other.root;
		other.root = nullptr;
		rank = other.rank;
		other.rank = static_cast<size_t>(-1);
	}
	return *this;
}

void BinomialTree::mergeTree(BinomialTree& other) {
	if (rank != other.rank)
		return;

	if (root->data < other.root->data) {
		other.root->rightSibling = root->leftChild;
		root->leftChild = other.root;
	}
	else {
		root->rightSibling = other.root->leftChild;
		other.root->leftChild = root;
		root = other.root;
	}

	other.root = nullptr;
	other.rank = static_cast<size_t>(-1);

	rank++;
}

int BinomialTree::getMin() const {
	if (isValid())
		return root->data;
	return INT_MAX;
}

size_t BinomialTree::getRank() const {
	return rank;
}

bool BinomialTree::isValid() const {
	return (rank != static_cast<size_t>(-1));
}

BinomialTree::~BinomialTree() {
	free(root);
}