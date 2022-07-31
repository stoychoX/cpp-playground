#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

#include"ChunkCollection.h"


class SparseTable {
	// indexes[k][i] -> Индексът на минимума в i-ти интервал с дължина 2^(k+1)
public:				// оправи това
	std::vector<std::vector<unsigned>> indexes;

	SparseTable() {}

	template<class T>
	void init(const ChunkCollection& arg, const RMQ01Info& info, const std::vector<T>& v) {
		std::vector<unsigned> beg;

		size_t chunkSize = arg.overallChunkSize();
		bool hasLastChunk = arg.hasLastChunk();
		size_t length = arg.chunkDatabaseSize();

		for (size_t i = 0; i < length - hasLastChunk; i++)
			beg.push_back(info.indexes[i * chunkSize + arg[i].getMin()]);

		if (hasLastChunk)
			beg.push_back(info.indexes[info.depths[(length - 1) * chunkSize + arg[length - 1].getMin()]]);

		indexes.push_back(beg);
		int at = 0;

		for (size_t i = 1; (1 << i) <= length; i++) {
			std::vector<unsigned> min;
			for (size_t j = 0; (j + (1 << i) - 1) < length; j++) {
				size_t firstIndex = j;
				size_t secondIndex = j + (1 << (i - 1));

				(v[indexes[at][firstIndex]] < v[indexes[at][secondIndex]]) ?
					min.push_back(indexes[at][firstIndex]) :
					min.push_back(indexes[at][secondIndex]);
			}
			indexes.push_back(min);
			++at;
		}
	}
};

#endif // !SPARSE_TABLE_H

