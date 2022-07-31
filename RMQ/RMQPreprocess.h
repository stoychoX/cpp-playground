#ifndef PP_RMQ_HEADER
#define PP_RMQ_HEADER

#include<vector>

struct RMQ01Info {
	std::vector<unsigned> depths;			// Дълбочините правещи RMQ01
	std::vector<unsigned> occurances;		// Кога за първи път сме видели възел k в масива с дълбочини?
	std::vector<int> indexes;				// Кой е индекса на дълбочина к?

	RMQ01Info() {}

	RMQ01Info(int n) {
		if (n == 0)
			return;

		depths.resize(2 * n - 1, -1);
		indexes.resize(2 * n - 1, -1);
		occurances.resize(n, -1);
	}
};

template<class T>
class RMQPreprocess {
private:
	class CartesianTree {
	public:
		struct Node {
			size_t idx;									// Индекс в оригиналния масив
			int left;									// Индекс на десния наследник в nodes (-1 ако няма)
			int right;									// Индекс на левия наследник в nodes (-1 ако няма)

			Node(size_t i, int l = -1, int r = -1) :
				idx(i),
				left(l),
				right(r) {}
		};

		std::vector<Node> nodes;
		int rootIndex;

		void buildFast(const std::vector<int>& init) {
			if (init.empty()) {
				rootIndex = -1;
				return;
			}

			rootIndex = 0;								// В началото корена е първия елемент
			nodes.push_back({ 0 });						// Добавяме го в масива отговарящ за представяне на дървото
			std::vector<int> rightSpine;				// Масив представящ десния гръбнак на дървото (индексите им)
			rightSpine.push_back(0);					// Десния гръбнак в началото е корена

			for (size_t i = 1; i < init.size(); i++) {
				const T& currentValue = init[i];		// Вземаме текущата стойност от масива.

				nodes.push_back({ i });					// Добавяме Node който съответства на нейния индекс.

				if (init[rightSpine.back()] < currentValue) {
					nodes[rightSpine.back()].right = i;
					// Ако тя е по - голяма от най - десния елемент я добавяме в края на гръбнака.
				}
				else {
					// В противен случай започваме да търсим правилното място по десния гръбнак.
					while (!rightSpine.empty() && !(init[rightSpine.back()] < currentValue)) {
						rightSpine.pop_back();
					}

					// Ако той е празен то това е нов минимум.
					if (rightSpine.empty()) {
						nodes[i].left = rootIndex;
						rootIndex = i;
					}
					else {
						int splitIndex = rightSpine.back();
						nodes[i].left = nodes[splitIndex].right;
						nodes[splitIndex].right = i;
						// Ако не е празен просто "сплитваме"
						// т.е. елемента заедно с лявото си поддърво става ляво
						// поддърво на сегашния елемент.
					}
				}
				rightSpine.push_back(i);
			}
		}

		CartesianTree(const std::vector<T>& init) {
			buildFast(init);
		}

		bool valid() const {
			return (rootIndex != -1);
		}
	};

	static void buildRMQ(const CartesianTree& tree, RMQ01Info& arg, int current, unsigned depth, unsigned& progress) {
		if (!tree.valid())
			return;

		int leftNodeIndex = tree.nodes[current].left;
		int rightNodeIndex = tree.nodes[current].right;
		int currentIndex = tree.nodes[current].idx;

		if (arg.occurances[currentIndex] == -1)
			arg.occurances[currentIndex] = progress;

		arg.depths[progress] = depth;
		arg.indexes[progress] = currentIndex;

		if (leftNodeIndex != -1) {
			buildRMQ(tree, arg, tree.nodes[current].left, depth + 1, ++progress);

			++progress;
			arg.depths[progress] = depth;
			arg.indexes[progress] = currentIndex;
		}

		if (rightNodeIndex != -1) {
			buildRMQ(tree, arg, tree.nodes[current].right, depth + 1, ++progress);

			++progress;
			arg.depths[progress] = depth;
			arg.indexes[progress] = currentIndex;
		}
	}

public:
	static RMQ01Info toRMQ01(const std::vector<T>& init) {
		CartesianTree ct(init);

		RMQ01Info toReturn(ct.nodes.size());

		unsigned progress = 0;

		buildRMQ(ct, toReturn, ct.rootIndex, 0, progress);

		return toReturn;
	}
};

#endif // !PP_RMQ_HEADER