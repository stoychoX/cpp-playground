﻿#ifndef AVL_TREE_HEADER
#define AVL_TREE_HEADER
#include<cassert>

// BF = height(right) - height(left) \in {-1, 0, 1}

class AVLTree {
private:
	struct Node {
		int data;
		int height;

		Node* left;
		Node* right;

		static void rotateLeft(Node*& subTree) {
			if (!subTree || !subTree->right)
				return;

			// std::swap
			int temp = subTree->data;
			subTree->data = subTree->right->data;
			subTree->right->data = temp;

			Node* originalRight = subTree->right;

			subTree->right = originalRight->right;

			originalRight->right = originalRight->left;

			originalRight->left = subTree->left;

			subTree->left = originalRight;
		}

		static void rotateRight(Node*& subTree) {
			if (!subTree || !subTree->left)
				return;

			// swap
			int temp = subTree->data;
			subTree->data = subTree->left->data;
			subTree->left->data = temp;

			Node* originalLeft = subTree->left;

			subTree->left = originalLeft->left;

			originalLeft->left = originalLeft->right;

			originalLeft->right = subTree->right;

			subTree->right = originalLeft;
		}

		static inline int max(int x, int y) {
			return (x > y) ? x : y;
		}

		static int getHeight(const Node const* r) {
			if (!r)
				return 0;
			return r->height;
		}

		static Node* copyDynamic(const Node* from) {
			if (!from)
				return nullptr;

			return new Node(from->data, copyDynamic(from->left), copyDynamic(from->right), from->height);
		}

		static bool compareNodes(const Node* first, const Node* second) {
			if (!first && !second)
				return true;

			if (!first || !second)
				return false;

			return (first->data == second->data) && compareNodes(first->left, second->left) && compareNodes(first->right, second->right);
		}

		Node(int data, Node* l = nullptr, Node* r = nullptr, int h = 1) : data(data), left(l), right(r), height(h) {}
	};

	Node* root;

	int pushRec(int elem, Node*& r);

	void freeRec(Node* r);

	void copy(const AVLTree& other);

	bool existRec(int elem, const Node* r) const;

	void free();
public:

	AVLTree() : root(nullptr) {}

	AVLTree(int data) : root(new Node(data)) {}

	AVLTree(const AVLTree& other) {
		copy(other);
	}

	AVLTree(AVLTree&& other); // Move semantics

	AVLTree& operator=(const AVLTree& other);

	AVLTree& operator=(AVLTree&& other);

	bool exists(int elem) const;

	void push(int elem);

	~AVLTree();
};

#endif // !AVL_TREE_HEADER
