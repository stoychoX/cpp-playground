#ifndef BIT_CHUNK_HEADER
#define BIT_CHUNK_HEADER
#include<vector>
#include<cassert>

class BitChunk {
	// Триъгълна таблица
	std::vector<std::vector<int>> data;
	size_t chunkSize;
	bool isValid;
public:
	BitChunk(size_t s) : chunkSize(s), isValid(false) {};

	template<class T>
	void init(const RMQ01Info& info, const std::vector<T>& init, size_t offset) {
		std::vector<std::vector<std::pair<int, int>>> temp;					// idx & depth
		temp.resize(chunkSize);
		data.resize(chunkSize);

		for (size_t i = 0; i < chunkSize; i++)
			temp[0].push_back({ i, info.depths[offset + i] });


		for (size_t i = 0; i < chunkSize - 1; i++) {
			for (size_t j = 0; j < temp[i].size() - 1; j++) {
				(temp[i][j].second < temp[i][j + 1].second) ?
					temp[i + 1].push_back(temp[i][j]) :
					temp[i + 1].push_back(temp[i][j + 1]);
			}
		}

		int cnt = 0;
		for (const auto& elem : temp) {
			for (const auto& pair : elem) {
				data[cnt].push_back(pair.first);
			}
			++cnt;
		}

		isValid = true;
	}

	unsigned getMinInRange(int start, int end) const {
		assert(std::abs(end - start) < chunkSize && isValid);

		int length = std::abs(end - start);
		int from = std::min(end, start);

		return data[length][from];
	}

	unsigned getMin() const {
		return getMinInRange(0, chunkSize - 1);
	}

	bool valid() const {
		return isValid;
	}

	size_t size() const {
		return chunkSize;
	}
};

#endif // !BIT_CHUNK_HEADER
