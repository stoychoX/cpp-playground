#include<vector>
#include<list>

using adjacencyList = std::vector<std::list<int>>;
using std::vector;

void mark(const adjacencyList&, std::vector<int>&, int, adjacencyList&, std::vector<bool>&);

// Returns transitive closure of a graph represented as adjacency list.
adjacencyList TC(const adjacencyList& graph) {
	adjacencyList toReturn = graph;

	vector<int> startEdges;

	for (size_t i = 0; i < graph.size(); i++) {
		vector<bool> visited(graph.size());
		
		startEdges.push_back(i);

		for (int vertex : graph[i])
			mark(graph, startEdges, vertex, toReturn, visited);

		startEdges.clear();
	}

	return toReturn;
}

void pushUnique(adjacencyList& toReturn, int idx, int vertex) {
	if (std::find(toReturn[idx].begin(), toReturn[idx].end(), vertex) == toReturn[idx].end())
		toReturn[idx].push_back(vertex);
}

void mark(const adjacencyList& graph, vector<int>& startEdges, int iterateEdge, adjacencyList& toReturn, vector<bool>& visited) {
	if (visited[iterateEdge])
		return;

	visited[iterateEdge] = true;

	for (int adjacentVertex : graph[iterateEdge]) {
		for (size_t i = 0; i < startEdges.size(); i++)
			pushUnique(toReturn, startEdges[i], adjacentVertex);

		startEdges.push_back(iterateEdge);
		mark(graph, startEdges, adjacentVertex, toReturn, visited);
	}
}
