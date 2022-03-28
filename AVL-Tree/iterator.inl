class iterator {
private:
	Node* currentNode;
public:
	iterator() = delete;

	iterator(const AVLTree& arg) : currentNode(arg.root) {}

	iterator(const iterator&) = default;

	iterator& operator++() {
		if (currentNode)
			currentNode = currentNode->right;
		return *this;
	}

	iterator& operator++(int) {
		return operator++();
	}

	iterator& operator--() {
		if (currentNode)
			currentNode = currentNode->left;
		return *this;
	}

	iterator& operator--(int) {
		return operator--();
	}

	int operator*() const {
		assert(isValid());
		return currentNode->data;
	}

	bool operator==(const iterator& it) const {
		return Node::compareNodes(currentNode, it.currentNode);
	}

	bool operator!=(const iterator& it) const {
		return !(*this == it);
	}

	bool isValid() const {
		return (currentNode != nullptr);
	}

	int currentVal() const {
		assert(isValid());

		return currentNode->data;
	}

	int height() const {
		assert(isValid());

		return currentNode->height;
	}
};