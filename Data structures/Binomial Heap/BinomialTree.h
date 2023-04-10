#ifndef BIN_TREE_HEADER
#define BIN_TREE_HEADER

class BinomialTree {
protected:
	struct Node {
		int data;
		Node* leftChild;
		Node* rightSibling;

		Node(int d, Node* lc = nullptr, Node* rs = nullptr) : data(d), leftChild(lc), rightSibling(rs) {}
	};

	Node* root;
	size_t rank;

	void free(Node*&);
	static int getData(const Node const* r);
public:
	friend class BinomialHeap;

	BinomialTree();
	BinomialTree(int data);

	BinomialTree(const BinomialTree&) = delete;
	BinomialTree& operator=(const BinomialTree&) = delete;

	// Object is move-only
	BinomialTree(BinomialTree&&);
	BinomialTree& operator=(BinomialTree&&);
	
	void mergeTree(BinomialTree&);
	int getMin() const;

	size_t getRank() const;
	bool isValid() const;

	~BinomialTree();
};

#endif
