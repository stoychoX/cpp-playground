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

		if (res == -1)
			return -1;

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

			if (r->right)
				r->right->height--;

			return 2;
		}
	}
	else {
		res = pushRec(elem, r->right);
		if (res == -1)
			return -1;

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

			if (r->left)
				r->left->height--;

			return 2;
		}
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

void AVLTree::free() {
	freeRec(root);
}

AVLTree::AVLTree(AVLTree&& other) {
	this->root = other.root;
	other.root = nullptr;
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
	}
	return *this;
}

bool AVLTree::exists(int elem) const {
	return existRec(elem, root);
}

AVLTree::iterator AVLTree::begin() const {
	return AVLTree::iterator(*this);
}

void AVLTree::push(int elem) {
	pushRec(elem, root);
}

AVLTree::~AVLTree() {
	free();
}
