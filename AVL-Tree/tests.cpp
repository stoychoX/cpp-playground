//www.github.com/doctest
#include "AVLTree.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include"doctest.h"
#include<cmath>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include<algorithm>

bool isAVL(const AVLTree::iterator& t) {
	if (!t.isValid())
		return true;
	int lHeight = (--t).getHeight();
	int rHeight = (++t).getHeight();

	return std::abs(rHeight - lHeight) < 2 && isAVL(++t) && isAVL(--t);
}

TEST_CASE("test on big tree") {
	int nodesCount = 1000000;

	AVLTree t;

	for (int i = 0; i < nodesCount; i++)
		t.push((rand() % (2 * nodesCount)) + 1);

	CHECK(isAVL(t.begin()));
}

TEST_CASE("test BST property and correct heigth on 100 random trees") {
	for (int i = 0; i < 100; i++) {
		AVLTree t;
		int randNumberOfNodes = rand() % 10000;

		for (int i = 0; i < randNumberOfNodes; i++)
			t.push(rand() % 10000);
		CHECK(isAVL(t.begin()));
	}
}

TEST_CASE("check on one element tree") {
	AVLTree t;
	t.push(1);

	CHECK(isAVL(t.begin()));
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

TEST_CASE("check removing one element") {
	AVLTree t;
	for (int i = 0; i < 10; i++)
		t.push(i);

	CHECK(t.exists(1));

	t.removeElement(1);

	CHECK(t.exists(1) == false);
}

TEST_CASE("check avl property after removing element with rotation") {
	AVLTree t;

	for (int i = 1; i < 10; i++)
		t.push(i);

	t.removeElement(6);

	CHECK(isAVL(t.begin()));
}

TEST_CASE("check avl property after removing a lot of elements") {
	AVLTree t;

	for (int i = 0; i < 100; i++)
		t.push(i);

	for (int i = 0; i < 100; i += 3) {
		t.removeElement(i);
		CHECK(isAVL(t.begin()));
	}
}

TEST_CASE("check nodes count") {
	AVLTree t;

	int length = 200;

	std::vector<int> v;

	v.reserve(length);

	for (int i = 0; i < length; i++)
		v.emplace_back(i);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));

	for (int i = 0; i < length; i++)
		t.push(v[i]);

	int cnt = length;

	CHECK(t.getNodesCount() == length);

	for (int i = 0; i < length; i++) {
		t.removeElement(v[i]);
		CHECK(isAVL(t.begin()));
	}
}