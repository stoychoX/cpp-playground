#ifndef RADIX_TREE_HEADER
#define RADIX_TREE_HEADER

#define TERMINAL_SYMBOL '$'

#include<string>
#include<cassert>
#include<array>
#include<algorithm>

enum class AlphabetType {
	OnlyLowerCase = 26 + 1,				// [a-z] + <TERMINAL_SYMBOL>
	AllLetters = 52 + 1,				// [a-z] + [A-Z] + <TERMINAL_SYMBOL> 
	ASCII = 127,
	ALL = 256
};

template<AlphabetType alphabet>
class RadixTree {
private:
	class Node {
	public:
		std::array<Node*, (size_t)(alphabet)> data;
		std::string word;
		uint16_t children;

		Node() { data = {}; children = 0; }

		Node(const std::string& w) : word(w), children(0), data({}) {}

		bool isWordEnd() const {
			return
				word.back() == TERMINAL_SYMBOL ||
				(data[getIndex(TERMINAL_SYMBOL)] != nullptr);
		}

		void markAsEnd() {
			if (isWordEnd()) return;

			if (children == 0)
				word.push_back(TERMINAL_SYMBOL);
			else
				data[getIndex(TERMINAL_SYMBOL)] = new Node();
		}

		void unmarkAsEnd() {
			delete data[getIndex(TERMINAL_SYMBOL)];
			data[getIndex(TERMINAL_SYMBOL)] = nullptr;

			if (word.back() == TERMINAL_SYMBOL)
				word.pop_back();
		}

		~Node() {
			for (size_t i = 0; i < data.size(); i++)
				delete data[i];
		}
	};

	static size_t getIndex(char c) {
		if (c == TERMINAL_SYMBOL)
			return 0;
		else if (c == 0)
			return (size_t)(TERMINAL_SYMBOL);


		size_t toReturn = 0;

		switch (alphabet) {
		case AlphabetType::OnlyLowerCase:
			toReturn = 1 + c - 'a';
			break;
		case AlphabetType::AllLetters:
			isupper(c) ?
				toReturn = 1 + 26 + c - 'A' :
				toReturn = 1 + c - 'a';
			break;
		case AlphabetType::ASCII:
			toReturn = (size_t)(c);
			break;
		case AlphabetType::ALL:
			toReturn = 128 + (int)(c);
			break;
		}

		return toReturn;
	}

	static bool isInvalidPrefix(size_t prefix, const Node* current) {
		return
			(prefix != current->word.size()) &&	// Префикса е по къс от самата дума. Тогава не можем да продължим.
			!((prefix == current->word.size() - 1) && current->word.back() == TERMINAL_SYMBOL);	// Понеже слагаме $ в края на думите без деца трябва да хванем този corner case
	}

	static bool isValidPrefix(size_t prefix, const std::string& arg, const Node* current) {
		return prefix == arg.size() &&
			(prefix == current->word.size() ||
				(prefix == current->word.size() - 1 && current->word.back() == TERMINAL_SYMBOL));
	}

	static void updateNode(Node*& current, const std::string& toAppend) {
		if (current == nullptr) {
			current = new Node(toAppend);
		}
		else {
			current->word = toAppend + current->word;
		}
	}

	void split(Node* current, const std::string& arg, size_t prefix) {
		const std::string& rootRigth = current->word.substr(prefix);
		const std::string& argumentRight = arg.substr(prefix);

		current->word = arg.substr(0, prefix);						// The common prefix

		if (rootRigth.size() == 1 && rootRigth[0] == TERMINAL_SYMBOL) {
			updateNode(current->data[getIndex(argumentRight[0])], argumentRight);
			current->children++;
			current->markAsEnd();
		}
		else {
			Node* newChild = new Node(rootRigth);
			newChild->children = current->children;
			current->children = 1;

			for (size_t i = 0; i < current->data.size(); i++) {
				newChild->data[i] = current->data[i];
				current->data[i] = nullptr;
			}

			if (current->isWordEnd()) {
				current->unmarkAsEnd();
				newChild->markAsEnd();
			}

			current->data[getIndex(rootRigth[0])] = newChild;
		}
	}

	void removeWord(Node*& current) {
		if (current->children == 0) {
			delete current;
			current = nullptr;
		}
		else if (current->children == 1) {
			current->unmarkAsEnd();
			Node* child = nullptr;

			for (size_t i = 1; i < current->data.size(); i++) {
				if (current->data[i]) {
					child = current->data[i];
					break;
				}
			}

			for (size_t i = 0; i < current->data.size(); i++) {
				current->data[i] = child->data[i];
				child->data[i] = nullptr;
			}

			current->word += child->word;
			current->children = child->children;
			delete child;
		}
		else {
			current->unmarkAsEnd();
		}
	}

	static size_t prefixLength(const std::string& fst, const std::string& snd) {
		size_t border = std::min(fst.length(), snd.length());

		for (int i = 0; i < border; i++)
			if (fst[i] != snd[i])
				return i;

		return border;
	}
public:
	RadixTree() {}

	void insert(std::string arg);

	bool search(std::string arg) const;

	bool remove(std::string arg);

	~RadixTree() {}

	friend class RadixTreeTester;
private:
	Node root;
};

#endif // !RADIX_TREE_HEADER

template<AlphabetType alphabet>
void RadixTree<alphabet>::insert(std::string arg) {
	if (arg.empty()) {
		root.markAsEnd();
		return;
	}

	size_t idx = getIndex(arg[0]);
	Node* current = &root;

	while (current->data[idx]) {
		current = current->data[idx];

		size_t prefix = prefixLength(arg, current->word);

		if (prefix != current->word.size())
			split(current, arg, prefix);

		arg = arg.substr(prefix);

		if (arg.empty()) {
			current->markAsEnd();
			return;
		}

		idx = getIndex(arg[0]);
	}

	if (current->data[idx] == nullptr) {
		current->data[idx] = new Node(arg);
		current->children += 1;
	}

	current->data[idx]->markAsEnd();
}

template<AlphabetType alphabet>
bool RadixTree<alphabet>::search(std::string arg) const {
	if (arg.empty())
		return root.isWordEnd();

	size_t idx = getIndex(arg[0]);
	const Node* current = &root;

	while (current->data[idx]) {
		current = current->data[idx];

		size_t prefix = prefixLength(current->word, arg);

		if (isInvalidPrefix(prefix, current))
			return false;
		if (isValidPrefix(prefix, arg, current))
			return current->isWordEnd();

		arg = arg.substr(prefix);
		idx = getIndex(arg[0]);
	}

	return false;
}

template<AlphabetType alphabet>
bool RadixTree<alphabet>::remove(std::string arg) {
	if (arg.empty()) {
		bool toReturn = root.isWordEnd();
		root.unmarkAsEnd();
		return toReturn;
	}

	Node* current = &root;
	Node* parent = &root;
	size_t idx = getIndex(arg[0]);

	while (current->data[idx] && !arg.empty()) {
		parent = current;
		Node*& refCurrent = current->data[idx];
		current = current->data[idx];

		size_t prefix = prefixLength(current->word, arg);

		if (isInvalidPrefix(prefix, current))
			return false;
		if (isValidPrefix(prefix, arg, current) && current->isWordEnd()) {
			bool removeChild = (current->children == 0);
			removeWord(refCurrent);
			parent->children -= removeChild;
			return true;
		}

		arg = arg.substr(prefix);

		idx = getIndex(arg[0]);
	}
	return false;
}