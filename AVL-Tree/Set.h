#ifndef SET_HEADER
#define SET_HEADER
#include"AVLTree.h"
#include<vector>

class Set {
private:
	AVLTree data;

	void construct(const AVLTree::iterator&, std::vector<int>&, int& index) const;

	int getMinElemRec(const AVLTree::iterator& it) const;
	int getMaxElemRec(const AVLTree::iterator& it) const;

public:
	int addElement(int elem);
	int removeElement(int elem);

	bool existsElement(int elem) const;

	size_t getCardinality() const;

	std::vector<int> getSorted() const;

	int getMinElem() const;
	int getMaxElem() const;

};
#endif // !define SET_HEADER


