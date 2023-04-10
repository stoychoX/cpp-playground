#ifndef VEB_TREE_IMPL
#define VEB_TREE_IMPL

#include<bit>
#include<cassert>
#include<vector>

/*
* Ползваме num_t за да може по - лесно да променяме типовете, с които дървото работи.
* Използваме -1 като "undefined" стойност.
*/

class vEBTree {
private:
	using num_t = unsigned long long;

	struct vbNode {
		size_t size;							// Колко елемента имаме.
		num_t min;								// Минимума в колекцията представена от възела.
		num_t max;								// Максимума в колекцията представена от възела.
		num_t bitwidth;							// Броя битове на най - голямото число във вселената.
		num_t pow;								// 2^{n >> 1} използваме го за high, low, pred, succ и др. - може да се махне
		vbNode* summary;						// summary вектор за непразните клъстъри.
		std::vector<vbNode*> clusters;			// Поддърветата, индексирани от първата половина на битовете на число.

		explicit vbNode(num_t n) :size{ 0 }, min{ undef() }, max{ undef() }, bitwidth{ n }, pow{ (num_t)(1LL << (n >> 1)) }, summary{ nullptr } {
			if (n <= 1) {
				return;
			}

			size_t clusterCount = (1 << (n - n / 2));
			size_t clusterRange = n / 2;

			size_t summarySize = n - n / 2;

			summary = new vbNode(summarySize);

			clusters.resize(clusterCount);

			for (size_t i = 0; i < clusterCount; i++)
				clusters[i] = new vbNode(clusterRange);
		}

		num_t high(num_t x) const {
			return x / pow;
		}

		num_t low(num_t x) const {
			return x % pow;
		}

		bool inUniverse(num_t x) const {
			return (x < (1LL << bitwidth));
		}

		/*
		* При празен възел минимума и максимума са равни.
		* При възел с един елемент определяме кой е минимума и кой максимума.
		* Ако добавяме елемент, който не е нов минимум или максимум, просто слизаме надолу в дървото.
		* В противен случай ъпдейтваме минимума или максимума и инсъртваме старата стойност надолу в дървото.
		* Последния else прави точно това.
		* Уваличаваме размера с единица, понеже предполагаме, че операцията винаги е успешна.
		*/
		void insert(num_t x) {
			if (size == 0) {
				min = max = x;
			}
			else if (size == 1) {
				max = std::max(min, x);
				min = std::min(min, x);
			}
			else if (x > min && x < max) {
				num_t idx = vbNode::high(x);
				num_t val = vbNode::low(x);

				if (clusters[idx]->size == 0)
					summary->insert(idx);

				clusters[idx]->insert(val);
			}
			else {
				num_t toInsert = (x < min) ? min : max;
				if (x < min)
					min = x;
				else
					max = x;

				size_t idx = vbNode::high(toInsert);
				size_t val = vbNode::low(toInsert);

				if (clusters[idx]->size == 0)
					summary->insert(idx);

				clusters[idx]->insert(val);
			}

			++size;
		}

		/*
		 * При извикване на този метод проверяваме, дали елемента се съдържа в дървото
		 * Ако стигнем до size == 0 то това вероятно е грешка при реализацията.
		 * При размер равен на 1 просто премахваме минимума и максимума.
		 * При размер равен на две, ъпдейтваме възела с коректни минимум/максимум.
		 * Ако не премахваме минимум или максимум просто премахваме елемента от съответното поддърво.
		 * Премахвайки максимума, за констаннтно време намираме предшественика му. Той е новия максимум. Премахваме предшественика от дървото и го слагаме като нов макс.
		 * Еквивалентно с наследника на най - малкия елемент. Сигурни сме, че такива има понеже размера е по - голям от 2.
		*/
		void remove(num_t x) {
			assert(size != 0);

			if (size == 1) {
				assert(min == max);
				assert(x == min);

				min = max = undef();
			}
			else if (size == 2) {
				assert(x == min || x == max);

				if (x == min)
					min = max;
				else
					max = min;
			}
			else if (x > min && x < max) {
				size_t idx = vbNode::high(x);
				size_t val = vbNode::low(x);

				if (clusters[idx]->size == 1)
					summary->remove(idx);

				clusters[idx]->remove(val);
			}
			else if (x == min) {
				num_t mSucc = this->minSucc();
				this->remove(mSucc);
				min = mSucc;
				return;
			}
			else if (x == max) {
				num_t mPred = this->maxPred();
				this->remove(mPred);
				max = mPred;
				return;
			}

			--size;
		}

		bool find(num_t x) const {
			if (size == 0) {
				return false;
			}
			else if (size == 1) {
				return x == max;
			}
			else if (size == 2) {
				return x == max || x == min;
			}

			if (x == max || x == min)
				return true;

			num_t idx = high(x);
			num_t val = low(x);

			return clusters[idx]->find(val);
		}

		num_t pred(num_t x) const {
			if (size == 0 || min > x)
				return undef();

			if (x >= max)
				return max;

			if (x == min) 
				return min;

			size_t idx = vbNode::high(x);
			size_t val = vbNode::low(x);

			num_t currentClusterPrec = clusters[idx]->pred(val);

			// Ако няма предшественик в този клъстър...
			if (currentClusterPrec == undef()) {
				num_t closestLeftNonEmptyCluster = summary->pred(idx - 1);

				if (closestLeftNonEmptyCluster == undef())
					return min;

				return pow * closestLeftNonEmptyCluster + clusters[closestLeftNonEmptyCluster]->max;
			}

			return pow * idx + currentClusterPrec;
		}

		num_t succ(num_t x) const {
			if (size == 0 || max < x)
				return undef();

			if (x <= min)
				return min;

			if (x == max)
				return max;

			size_t idx = vbNode::high(x);
			size_t val = vbNode::low(x);

			num_t currentClusterSucc = clusters[idx]->succ(val);

			if (currentClusterSucc == undef()) {
				num_t closestRightNonEmptyCluster = summary->succ(idx + 1);

				if (closestRightNonEmptyCluster == undef())
					return max;

				return pow * closestRightNonEmptyCluster + clusters[closestRightNonEmptyCluster]->min;
			}
			return pow * idx + currentClusterSucc;
		}

		num_t maxPred() const {
			if (size < 2)
				return undef();
			else if (size == 2)
				return min;

			size_t idx = summary->max;
			size_t off = clusters[idx]->max;

			return idx * pow + off;
		}

		num_t minSucc() const {
			if (size < 2)
				return undef();
			else if (size == 2)
				return max;

			size_t idx = summary->min;
			size_t off = clusters[idx]->min;

			return idx * pow + off;
		}

		~vbNode() {
			if (bitwidth <= 1) { return; }

			for (size_t i = 0; i < clusters.size(); i++)
				delete clusters[i];

			delete summary;
		}
	};

	static num_t undef() {
		return static_cast<num_t>(-1);
	}

	vbNode root;

	static bool isPowerOfTwo(num_t u) {
		return u != 0 && ((u & (u - 1)) == 0);
	}

	static num_t toPowerOfTwo(num_t u) {
		if (isPowerOfTwo(u)) {
			return u;
		}

		return (1LL << std::bit_width(u));
	}

public:
	vEBTree(num_t u);

	vEBTree(const vEBTree&) = delete;
	vEBTree& operator=(const vEBTree&) = delete;

	void insert(num_t x);

	void remove(num_t x);

	bool find(num_t x) const;

	num_t pred(num_t x) const;

	num_t succ(num_t x) const;

	num_t maxPred() const;

	num_t minSucc() const;

	size_t universe() const;

	size_t size() const;

	num_t min() const;

	num_t max() const;

	bool empty() const;
};

#endif // !VEB_TREE_IMPL
