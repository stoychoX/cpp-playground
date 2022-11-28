#include"vEBTree.h"

vEBTree::vEBTree(num_t u) : root{ vbNode(std::bit_width(toPowerOfTwo(u) - 1)) } {}

void vEBTree::insert(num_t x) {
	if (!root.inUniverse(x) || find(x))
		return;

	root.insert(x);
}

void vEBTree::remove(num_t x) {
	if (!root.inUniverse(x) || !find(x))
		return;

	root.remove(x);
}

bool vEBTree::find(num_t x) const {
	if (!root.inUniverse(x))
		return false;

	return root.find(x);
}

vEBTree::num_t vEBTree::pred(num_t x) const {
	return root.pred(x);
}

vEBTree::num_t vEBTree::succ(num_t x) const {
	return root.succ(x);
}

vEBTree::num_t vEBTree::maxPred() const {
	return root.maxPred();
}

vEBTree::num_t vEBTree::minSucc() const {
	return root.minSucc();
}

size_t vEBTree::universe() const {
	return (1LL << root.bitwidth);
}

size_t vEBTree::size() const {
	return root.size;
}

vEBTree::num_t vEBTree::min() const {
	return root.min;
}

vEBTree::num_t vEBTree::max() const {
	return root.max;
}

bool vEBTree::empty() const {
	return root.size == 0;
}