//www.github.com/doctest
#include "AVLTree.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include"doctest.h"
#include<cmath>

bool isBST(AVLTree::iterator it, int max = INT_MAX, int min = INT_MIN) {
	if (!it.isValid())
		return true;

	if (*it < min || *it > max)
		return false;

	return isBST(++it, max, it.currData()) && isBST(--it, it.currData(), min);
}

bool correctHeight(const AVLTree& t) {
	int lowerBound = log2(t.getNodesCount());
	int upperBound = 2 * log2(t.getNodesCount()) + 2;

	return lowerBound <= t.getHeight() && t.getHeight() <= upperBound;
}

bool isAVL(const AVLTree& t) {
	return isBST(t.begin()) && correctHeight(t);
}

TEST_CASE("test BST property and correct heigth on 100 random trees") {
	for (int i = 0; i < 100; i++) {
		AVLTree t;
		int randNumberOfNodes = rand() % 10000;

		for (int i = 0; i < randNumberOfNodes; i++)
			t.push(rand() % 10000);
		CHECK(isAVL(t));
	}
}

TEST_CASE("check if find works") {
	AVLTree t;
	
	int toFild = rand() % 100 + 1;

	for (int i = 0; i < 100; i++)
		t.push(rand() % 1000 + 1);

	t.push(toFild);

	CHECK(t.exists(toFild));
	CHECK(t.exists(0) == false);
}

TEST_CASE("check if nodes count is correct") {
	AVLTree t;
	int len = rand() % 100;

	for (int i = 0; i < len; i++)
		t.push(i);

	CHECK(t.getNodesCount() == len);
}
