#include<iostream>
#include<vector>
#include<list>
#include<optional>
#include<queue>

using Vertex = unsigned int;

struct Edge {
	Vertex from;
	Vertex to;
};

struct WeightedEdge {
	Edge edge;
	int weigth;
};

void relax(std::vector<int>& res, const WeightedEdge& e) {
	int alternativePath = res[e.edge.from] + e.weigth;
	int currentPath = res[e.edge.to];

	if (alternativePath < currentPath)
		res[e.edge.to] = alternativePath;
}

void relax(std::vector<size_t>& res, const WeightedEdge& e) {
	int alternativePath = res[e.edge.from] + e.weigth;
	int currentPath = res[e.edge.to];

	if (alternativePath < currentPath)
		res[e.edge.to] = alternativePath;
}

class WeightedGraph {
	std::vector<std::list<WeightedEdge>> data;
	size_t graphSize;
public:
	WeightedGraph(size_t n) {
		graphSize = n;
		data = std::vector<std::list<WeightedEdge>>(n, std::list<WeightedEdge>());
	}

	void addDirectedEdge(Vertex from, Vertex to, int w = 0) {
		if (from > graphSize || to > graphSize)
			return;

		data[from].push_back({ from, to, w });
	}

	void addEdge(Vertex from, Vertex to, int w = 0) {
		addDirectedEdge(from, to, w);
		addDirectedEdge(to, from, w);
	}

	size_t size() const {
		return graphSize;
	}

	std::optional<std::vector<int>> bellmanFord(Vertex from) const;

	std::vector<std::vector<int>> floydWarshall() const;

	std::vector<size_t> dijkstra(Vertex start) const;

	bool canBeRelaxed(const std::vector<int>& res, const WeightedEdge& e) const;
	bool canBeRelaxed(const std::vector<size_t>& res, const WeightedEdge& e) const;

	void floydWarshallDemo() const;
	void bellmanFordDemo() const;
	void dijkstraDemo() const;
};

std::optional<std::vector<int>> WeightedGraph::bellmanFord(Vertex from) const {
	std::vector<int> result(size(), INT_MAX);

	result[from] = 0;

	for (size_t i = 0; i < size() - 1; i++) {
		for (size_t vertexFrom = 0; vertexFrom < size(); vertexFrom++) {
			for (const WeightedEdge& e : data[vertexFrom]) {
				relax(result, e);
			}
		}
	}

	std::optional<std::vector<int>> toReturn;

	for (size_t i = 0; i < size(); i++) {
		for (const WeightedEdge& e : data[i]) {
			if (canBeRelaxed(result, e)) {
				toReturn.reset();
				return toReturn;
			}
		}
	}
	toReturn.emplace(result);
	return toReturn;
}

std::vector<std::vector<int>> WeightedGraph::floydWarshall() const {
	std::vector<std::vector<int>> result(graphSize, std::vector<int>(graphSize, INT_MAX));

	for (size_t i = 0; i < graphSize; i++) {
		for (const WeightedEdge& e : data[i])
			result[i][e.edge.to] = e.weigth;

		result[i][i] = 0;
	}

	for (size_t k = 0; k < graphSize; k++)
		for (size_t i = 0; i < graphSize; i++)
			for (size_t j = 0; j < graphSize; j++)
				if ((result[i][k] != INT_MAX && result[k][j] != INT_MAX) && (result[i][j] > result[i][k] + result[k][j]))
					result[i][j] = result[i][k] + result[k][j];

	return result;
}

std::vector<size_t> WeightedGraph::dijkstra(Vertex start) const {
	std::vector<size_t> table(graphSize, INT_MAX);

	table[start] = 0;

	struct Distance {
		Vertex vertex;
		size_t dist;

		bool operator<(const Distance& other) const {
			return dist < other.dist;
		}
	};

	std::priority_queue<Distance> q;

	q.push({ start, 0 });

	while (!q.empty()) {
		Distance current = q.top();
		q.pop();

		for (const WeightedEdge& e : data[current.vertex]) {
			if (canBeRelaxed(table, e)) {
				relax(table, e);
				q.push({ e.edge.to, table[e.edge.to] });
			}
		}
	}

	return table;
}

bool WeightedGraph::canBeRelaxed(const std::vector<int>& res, const WeightedEdge& e) const {
	return (res[e.edge.from] + e.weigth < res[e.edge.to]);
}

bool WeightedGraph::canBeRelaxed(const std::vector<size_t>& res, const WeightedEdge& e) const {
	return (res[e.edge.from] + e.weigth < res[e.edge.to]);
}

void WeightedGraph::floydWarshallDemo() const {
	auto result = floydWarshall();

	for (size_t i = 0; i < result.size(); i++) {
		for (size_t j = 0; j < result[i].size(); j++) {
			std::cout.width(3);
			if (result[i][j] != INT_MAX)
				std::cout << result[i][j];
			else
				std::cout << "#";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void WeightedGraph::bellmanFordDemo() const {
	auto res = bellmanFord(0);
	std::cout << "BF starting from vertex 0: " << std::endl;

	if (res) {
		for (size_t i = 0; i < res.value().size(); i++)
			std::cout << res.value()[i] << " ";

		std::cout << std::endl;
		return;
	}
	std::cout << "Negative cycle found!" << std::endl;
}

void WeightedGraph::dijkstraDemo() const {
	std::cout << "DJ starting from vertex 0: " << std::endl;

	auto res = dijkstra(0);

	for (size_t i = 0; i < res.size(); i++) {
		if (res[i] != INT_MAX)
			std::cout << res[i] << " ";
		else
			std::cout << "# ";
	}
	std::cout << std::endl;
}

int main() {
	WeightedGraph g(8);

	// Example: https://media.geeksforgeeks.org/wp-content/uploads/multi-stage-graph.jpg
	g.addDirectedEdge(0, 1, 1);
	g.addDirectedEdge(0, 2, 2);
	g.addDirectedEdge(0, 3, 5);
	g.addDirectedEdge(1, 4, 4);
	g.addDirectedEdge(1, 5, 11);
	g.addDirectedEdge(2, 4, 9);
	g.addDirectedEdge(2, 5, 5);
	g.addDirectedEdge(2, 6, 16);
	g.addDirectedEdge(3, 6, 2);
	g.addDirectedEdge(4, 7, 18);
	g.addDirectedEdge(5, 7, 13);
	g.addDirectedEdge(6, 7, 2);

	g.floydWarshallDemo();
	g.bellmanFordDemo();
	g.dijkstraDemo();
}
