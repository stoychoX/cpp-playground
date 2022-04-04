#include "AVLTree.h"

//-1 Провалено вмъкване
// 1 Вмъкването е ок
// 2 Вмъкването е ок и сме направили ротация
int AVLTree::pushRec(int elem, Node*& r) {
	int res = 0;

	if (r == nullptr) {
		r = new Node(elem);
		return 1;
	}
	else if (r->data == elem) {
		return -1;
	}
	else if (elem < r->data) {
		res = pushRec(elem, r->left);

		if (res != 1)
			return res;

		if (searchForLeftDisbalance(r) == 1)
			return 2;
	}
	else {
		res = pushRec(elem, r->right);

		if (res != 1)
			return res;

		if (searchForRightDisbalance(r) == 1)
			return 2;
	}

	r->height = Node::max(Node::getHeight(r->left), Node::getHeight(r->right)) + 1;	// Увеличаваме височината само ако не сме направили ротация
	return res;																		// Ако сме направили ротация връщаме отново 2
}

void AVLTree::freeRec(Node* r) {
	if (!r)
		return;
	freeRec(r->left);
	freeRec(r->right);

	delete r;
}

void AVLTree::copy(const AVLTree& other) {
	this->root = Node::copyDynamic(other.root);
	nodesCount = other.nodesCount;
}

int AVLTree::removeRec(Node*& r, int elem) {
	if (r == nullptr)
		return -1;

	int res = 1;

	if (r->data == elem) {
		if (!r->left && !r->right) {
			delete r;
			r = nullptr;
			return 1;
		}
		else if ((r->left && !r->right) || (!r->left && r->right)) {
			r->data = r->left ? r->left->data : r->right->data;

			if (r->left) {
				delete r->left;
				r->left = nullptr;
			}
			else {
				delete r->right;
				r->right = nullptr;
			}

			r->height = 1;

			return 1;
		}
		else {
			r->data = findMinLeft(r->right)->data;
			res = removeRec(r->right, r->data);
		}
	}
	else if (r->data > elem) {
		res = removeRec(r->left, elem);
	}
	else {
		res = removeRec(r->right, elem);
	}
	
	if (res != 1)
		return res;
	
	searchForLeftDisbalance(r);
	searchForRightDisbalance(r);

	r->height = Node::max(Node::getHeight(r->left), Node::getHeight(r->right)) + 1;

	return res;
}

AVLTree::Node* AVLTree::findMinLeft(Node* r) const {
	assert(r != nullptr);

	if (!r->left)
		return r;
	return findMinLeft(r->left);
}

bool AVLTree::existRec(int elem, const Node* r) const {
	if (r == nullptr)
		return false;
	else if (r->data == elem)
		return true;
	else if (r->data < elem)
		return existRec(elem, r->right);
	else
		return existRec(elem, r->left);
}

int AVLTree::searchForLeftDisbalance(Node*& r) {
	int balance = 0;
	int balanceRight = 0;

	balance += r->right ? r->right->height : 0;
	balance -= r->left ? r->left->height : 0;

	if (r->left) {
		balanceRight += r->left->right ? r->left->right->height : 0;
		balanceRight -= r->left->left ? r->left->left->height : 0;
	}

	if (balance == -2) {
		if (balanceRight == 1) {
			AVLTree::Node::rotateLeft(r->left);
		}

		AVLTree::Node::rotateRight(r);

		if (r->right) {
			r->right->height = Node::max(Node::getHeight(r->right->left), Node::getHeight(r->right->right)) + 1;
		}

		return 1;
	}

	return 0;
}

int AVLTree::searchForRightDisbalance(Node*& r) {
	int balance = 0;
	int balanceLeft = 0;

	balance += r->right ? r->right->height : 0;
	balance -= r->left ? r->left->height : 0;

	if (r->right) {
		balanceLeft += r->right->right ? r->right->right->height : 0;
		balanceLeft -= r->right->left ? r->right->left->height : 0;
	}

	if (balance == 2) {
		if (balanceLeft == -1) {
			AVLTree::Node::rotateRight(r->right);
		}

		AVLTree::Node::rotateLeft(r);

		if (r->left) {
			r->left->height = Node::max(Node::getHeight(r->left->left), Node::getHeight(r->left->right)) + 1;
			//r->left->height--;
		}

		return 1;
	}

	return 0;
}

void AVLTree::free() {
	freeRec(root);
}

AVLTree::AVLTree(AVLTree&& other) {
	this->root = other.root;
	other.root = nullptr;
	nodesCount = other.nodesCount;
}

AVLTree& AVLTree::operator=(const AVLTree& other) {
	if (this != &other) {
		free();
		copy(other);
	}

	return *this;
}

AVLTree& AVLTree::operator=(AVLTree&& other) {
	if (this != &other) {
		free();

		this->root = other.root;
		other.root = nullptr;
		nodesCount = other.nodesCount;
	}
	return *this;
}

bool AVLTree::exists(int elem) const {
	return existRec(elem, root);
}

int AVLTree::getNodesCount() const {
	return nodesCount;
}

int AVLTree::removeElement(int elem) {
	int res = removeRec(root, elem);

	if (res != -1)
		nodesCount--;

	return res;
}

AVLTree::iterator AVLTree::begin() const {
	return AVLTree::iterator(*this);
}

int AVLTree::push(int elem) {
	int res = pushRec(elem, root);

	if (res != -1)
		++nodesCount;

	return res;
}

int AVLTree::getHeight() const {
	return root ? root->height : 0;
}

bool AVLTree::isEmpty() const {
	return (root == nullptr);
}

AVLTree::~AVLTree() {
	free();
}
