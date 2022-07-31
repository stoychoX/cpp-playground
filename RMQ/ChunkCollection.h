#ifndef CHUNK_COLLECTION_HEADER
#define CHUNK_COLLECTION_HEADER

#include"BitChunk.h"
#include<cmath>

class ChunkCollection {
	std::vector<BitChunk> allChunkTypes;									// Всеки възможен чънк е кеширан тук
	std::vector<unsigned> data;												// Държи информация за типовете на чънковете.

public:
	static unsigned getBitwiseIndex(const std::vector<unsigned>& depths, size_t off, size_t size) {
		unsigned res = 0;

		for (size_t i = off + 1; i < off + size; i++)
			if (depths[i - 1] < depths[i])
				res |= 1 << i - off - 1;

		return res;
	}
	ChunkCollection() { }

	template<class T>
	void init(const RMQ01Info& info, const std::vector<T>& init) {
		if (init.empty())
			return;

		size_t logDown = log2(info.depths.size());
		size_t chunkSize = logDown / 2;

		if (chunkSize < 2)
			chunkSize = 2;

		size_t chunksCount = info.depths.size() / chunkSize;
		size_t differentChunksAvaiable = (1 << (chunkSize - 1));			// различните булеви вектори 2^{размера на чънка}

		allChunkTypes.resize(differentChunksAvaiable, BitChunk(chunkSize));

		for (size_t i = 0; i < chunksCount; i++) {
			unsigned indexOfCurrentChunk = getBitwiseIndex(info.depths, i * chunkSize, chunkSize);

			if (!allChunkTypes[indexOfCurrentChunk].valid())
				allChunkTypes[indexOfCurrentChunk].init<T>(info, init, i * chunkSize);

			data.push_back(indexOfCurrentChunk);
		}

		// Get last chunk
		size_t lastChunkSize = info.depths.size() % chunkSize;

		if (!lastChunkSize)
			return;

		BitChunk toAdd(lastChunkSize);

		toAdd.init<T>(info, init, chunkSize * chunksCount);
		allChunkTypes.push_back(toAdd);
		data.push_back(allChunkTypes.size() - 1);
	}

	int getMinIndex(size_t fromChunk, int start, int end) {
		assert(fromChunk < allChunkTypes.size());

		return allChunkTypes[data[fromChunk]].getMinInRange(start, end);
	}

	const BitChunk& operator[](size_t idx) const {
		assert(idx < data.size());
		return allChunkTypes[data[idx]];
	}

	size_t chunksCount() const { return allChunkTypes.size(); }

	size_t chunkDatabaseSize() const { return data.size(); }

	bool hasLastChunk() const {
		return (allChunkTypes.size() % 2 == 1);
	}

	size_t overallChunkSize() const {
		return allChunkTypes[0].size();
	}

	size_t lastSize() const {
		return allChunkTypes.back().size();
	}
};

#endif // !CHUNK_COLLECTION_HEADER
