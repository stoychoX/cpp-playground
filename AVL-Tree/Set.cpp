#include "Set.h"

void Set::construct(const AVLTree::iterator& t, std::vector<int>& sortedData, int& index) const {
    if (!t.isValid())
        return;

    construct(--t, sortedData, index);

    sortedData[index++] = t.currData();

    construct(++t, sortedData, index);
}

int Set::getMinElemRec(const AVLTree::iterator& it) const {
    const AVLTree::iterator left = --it;
    if (!left.isValid())
        return it.currData();

    return getMinElemRec(left);
}

int Set::getMaxElemRec(const AVLTree::iterator& it) const {
    const AVLTree::iterator right = ++it;
    if (!right.isValid())
        return it.currData();

    return getMaxElemRec(right);
}

int Set::addElement(int elem) {
    return data.push(elem);
}

int Set::removeElement(int elem) {
    return data.removeElement(elem);
}

bool Set::existsElement(int elem) const {
    return data.exists(elem);
}

size_t Set::getCardinality() const {
    return data.getNodesCount();
}

std::vector<int> Set::getSorted() const {
    std::vector<int> toReturn;
    toReturn.resize(data.getNodesCount());

    int index = 0;

    construct(data.begin(), toReturn, index);

    return toReturn;
}

int Set::getMinElem() const {
    if (!data.begin().isValid())
        return INT_MIN;

    return getMinElemRec(data.begin());
}

int Set::getMaxElem() const {
    if (!data.begin().isValid())
        return INT_MAX;

    return getMaxElemRec(data.begin());
}
