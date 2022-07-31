#ifndef RANGE_MINIMUM_QUERY_HEADER
#define RANGE_MINIMUM_QUERY_HEADER

#include "RMQPreprocess.h"
#include"SparseTable.h"
#include<cmath>

template<class T>
class RMQ {
private:
	RMQ01Info RMQ01Data;
	ChunkCollection chunks;
	SparseTable sparse;
	const std::vector<T>* data;

	// По - ниската степен на двойката. Използваме го за да намерим дължината на интервала.
	static size_t closestPowerOfTwo(size_t arg) {
		assert(arg != 0);

		arg |= arg >> 1;
		arg |= arg >> 2;
		arg |= arg >> 4;
		arg |= arg >> 8;
		arg |= arg >> 16;
		++arg;

		return (arg >> 1);
	}

	// От степен на двойката вземаме индекс, който ни води в правилната позиция на спарс таблицата.
	static size_t powerOfTwoToIndex(size_t powerOfTwo) {
		assert(powerOfTwo != 0 && ((powerOfTwo & (powerOfTwo - 1)) == 0));

		size_t toReturn = 0;

		while (powerOfTwo) {
			powerOfTwo >>= 1;
			++toReturn;
		}

		return (toReturn - 1);
	}

	// Вземаме лява и дясна позиция на чънк и намираме минимума между тях.
	size_t sparseMin(size_t leftChunkPos, size_t rigthChunkPos) const {
		size_t intrervalLen = closestPowerOfTwo(rigthChunkPos - leftChunkPos - 1);

		size_t idx = powerOfTwoToIndex(intrervalLen);

		size_t l = sparse.indexAt(idx, leftChunkPos + 1);

		// Гаден корнър кейс
		if (rigthChunkPos - leftChunkPos - 1 == intrervalLen)
			return l;

		size_t r = sparse.indexAt(idx, rigthChunkPos - intrervalLen);

		return ((*data)[l] < (*data)[r]) ? l : r;
	}

	size_t chunkMinToEnd(size_t left) const {
		size_t chunkSize = chunks.overallChunkSize();

		size_t startIndex = left / chunkSize;
		size_t startSize = chunks[startIndex].size();
		size_t leftMin = chunks[startIndex].getMinInRange(left % startSize, startSize - 1);

		return leftMin;
	}

	size_t chunkMinFromStart(size_t right) const {
		size_t chunkSize = chunks.overallChunkSize();

		size_t endIndex = right / chunkSize;
		size_t endSize = chunks[endIndex].size();
		size_t rightMin = chunks[endIndex].getMinInRange(0, right % endSize);

		return rightMin;
	}

public:
	RMQ(const std::vector<T>& init) {
		RMQ01Data = RMQPreprocess<T>::toRMQ01(init);
		chunks.init(RMQ01Data, init);
		sparse.init<T>(chunks, RMQ01Data, init);
		data = &init;
	}

	size_t min(size_t left, size_t right) const {
		assert(left < RMQ01Data.occurances.size() &&
			right < RMQ01Data.occurances.size());

		left = RMQ01Data.occurances[left];
		right = RMQ01Data.occurances[right];

		if (left > right)
			std::swap(left, right);

		if (left == right)
			return RMQ01Data.indexes[left];

		size_t chunkSize = chunks.overallChunkSize();

		size_t leftChunkPos = left / chunkSize;
		size_t rightChunkPos = right / chunkSize;

		if (leftChunkPos == rightChunkPos) {
			size_t minInChunk = chunks[leftChunkPos].getMinInRange(left % chunkSize, right % chunkSize);
			size_t off = chunkSize * leftChunkPos;

			return  RMQ01Data.indexes[off + minInChunk];
		}

		size_t toReturn;
		bool sparseNeeded = (rightChunkPos - leftChunkPos) > 1;

		if (sparseNeeded)
			toReturn = sparseMin(leftChunkPos, rightChunkPos);

		size_t leftMinIdx = RMQ01Data.indexes[leftChunkPos * chunkSize + chunkMinToEnd(left)];
		size_t rightMinIdx = RMQ01Data.indexes[rightChunkPos * chunkSize + chunkMinFromStart(right)];

		(sparseNeeded) ?
			toReturn = ((*data)[toReturn] < (*data)[leftMinIdx]) ? toReturn : leftMinIdx :
			toReturn = leftMinIdx;

		toReturn = (*data)[toReturn] < (*data)[rightMinIdx] ? toReturn : rightMinIdx;

		return toReturn;
	}
};

#endif // !RANGE_MINIMUM_QUERY_HEADER