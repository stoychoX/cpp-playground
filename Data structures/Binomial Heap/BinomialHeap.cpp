#include"BinomialHeap.h"

BinomialHeap::BinomialHeap() {}

BinomialHeap::BinomialHeap(int elem) {
	data.push_back(std::move(BinomialTree(elem)));
}

void BinomialHeap::merge(BinomialHeap& toMerge) {
	BinomialTree carry;

	if (!data.size()) {
		data.resize(toMerge.data.size());

		for (int i = 0; i < toMerge.data.size(); i++)
			data[i] = std::move(toMerge.data[i]);

		return;
	}

	int length = data.size() < toMerge.data.size() ? data.size() : toMerge.data.size();

	for (int i = 0; i < length; i++) {
		if (!data[i].isValid() && !toMerge.data[i].isValid()) {							// 0, 0
			data[i] = std::move(carry);
		}
		else if (data[i].isValid() && !toMerge.data[i].isValid()) {						// 1, 0
			if (carry.isValid()) {
				data[i].mergeTree(carry);
				carry = std::move(data[i]);
			}
		}
		else if (!data[i].isValid() && toMerge.data[i].isValid()) {						// 0, 1
			if (!carry.isValid()) {
				data[i] = std::move(toMerge.data[i]);
			}
			else {
				toMerge.data[i].mergeTree(carry);
				carry = std::move(toMerge.data[i]);
			}
		}
		else {																		   // 1, 1
			if (!carry.isValid()) {
				data[i].mergeTree(toMerge.data[i]);
				carry = std::move(data[i]);
			}
			else {
				BinomialTree temp = std::move(carry);
				data[i].mergeTree(toMerge.data[i]);
				carry = std::move(data[i]);
				data[i] = std::move(temp);
			}
		}
	}

	while (carry.isValid()) {
		if (length < data.size() && data[length].isValid()) {
			data[length].mergeTree(carry);
			carry = std::move(data[length]);
		}
		else if (length == data.size()) {
			if (length < toMerge.data.size() && toMerge.data[length].isValid()) {
				toMerge.data[length].mergeTree(carry);
				carry = std::move(toMerge.data[length]);

				data.push_back(std::move(BinomialTree()));
			}
			else {
				data.push_back(std::move(carry));
			}
		}
		else
			data[length] = std::move(carry);

		length++;
	}

	for (int i = length; i < toMerge.data.size(); i++)
		data.push_back(std::move(toMerge.data[i]));

	toMerge.flush();
}

void BinomialHeap::insert(int elem) {
	BinomialHeap toMerge(elem);
	merge(toMerge);
}

int BinomialHeap::getMin() const {
	int toReturn = INT_MAX;
	for (int i = 0; i < data.size(); i++)
		if (toReturn > data[i].getMin())
			toReturn = data[i].getMin();
	return toReturn;
}

int BinomialHeap::extractMin() {
	BinomialTree temp;
	BinomialHeap dummy;

	int minIndex = 0;

	for (int i = 1; i < data.size(); i++)
		if (data[minIndex].getMin() > data[i].getMin())
			minIndex = i;

	if (data[minIndex].root == nullptr)
		return data[minIndex].getMin();

	temp = std::move(data[minIndex]);

	int toReturn = temp.getMin();

	BinomialTree::Node* it = temp.root->leftChild;
	int rankCounter = temp.rank;
	int i = 0;

	dummy.data.resize(temp.rank);

	while (it) {
		BinomialTree::Node* next = it->rightSibling;

		BinomialTree toAdd;
		it->rightSibling = nullptr;
		toAdd.root = it;
		toAdd.rank = --rankCounter;
		dummy.data[i++] = std::move(toAdd);

		it = next;
	}

	delete temp.root;
	temp.root = nullptr;

	std::reverse(dummy.data.begin(), dummy.data.end());

	merge(dummy);

	return toReturn;
}

bool BinomialHeap::empty() const {
	for (int i = 0; i < data.size(); i++)
		if (data[i].isValid())
			return false;

	return true;
}

void BinomialHeap::flush() {
	while (!data.empty() && !data.back().isValid()) {
		data.pop_back();
	}
	data.shrink_to_fit();
}
