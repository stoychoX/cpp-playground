#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<string>

using vertex_t = unsigned int;
using weight_t = unsigned int;

struct Edge {
	vertex_t to;
	weight_t weight;
};

// Directed, weighted graph.
// graph[1] = { {0, 4}, {7, 3} } means we have the following edges:
// 1 --(4)--> 0
// 1 --(3)--> 7
using graph = std::vector<std::vector<Edge>>;

void addEdge(graph& g, vertex_t from, vertex_t to, weight_t w) {
	g[from].push_back({ to, w });
	g[to].push_back({ from, w });
}

void addDirectedEdge(graph& g, vertex_t from, vertex_t to, weight_t w) {
	g[from].push_back({ to, w });
}

vertex_t find(std::vector<vertex_t>& uf, vertex_t v) {
	if (v != uf[v]) {
		uf[v] = find(uf, uf[v]);
	}

	return uf[v];
}

void unionFunc(std::vector<vertex_t>& uf, vertex_t parent, vertex_t child) {
	uf[find(uf, child)] = find(uf, parent);
}

std::string prettyVertex(size_t vert, int step) {
	std::string v = '\"' + std::to_string(vert);

	v += '_' + std::to_string(step);

	v += '\"';

	return v;
}

void displayUF(std::vector<vertex_t>& parent, size_t step, bool end, const char* filepath) {
	std::ofstream outFile(filepath, std::ios::app);

	if (step == 0)
		outFile << "digraph MST {" << std::endl;

	outFile << "\t// union find used on step " << step + 1 << std::endl;

	for (size_t i = 0; i < parent.size(); i++)
		outFile << "\t" << prettyVertex(i, step) << " -> " << prettyVertex(parent[i], step) << ";" << std::endl;

	outFile << std::endl;

	if (end)
		outFile << std::endl << "}";
}

void displayGraph(graph& g, bool directed, const char* pathname) {
	std::ofstream outFile(pathname, std::ios::trunc);

	std::string transition = directed ? " -> " : " -- ";

	if (!directed)
		outFile << "graph G {" << std::endl;
	else
		outFile << "digraph G {" << std::endl;

	for (size_t i = 0; i < g.size(); i++) {
		for (const auto& e : g[i]) {
			outFile << i << transition << e.to << "[label=\"" << e.weight << "\"];" << std::endl;
		}
	}

	outFile << std::endl << "}";
}

// Visualization of Kruskal's algorithm
graph kruskal(const graph& g, const char* filepath) {
	std::vector<vertex_t> uf(g.size());
	graph result(g.size());

	for (size_t i = 0; i < g.size(); i++)
		uf[i] = i;

	// sort edges using multimap w -> {from, to}
	std::multimap<weight_t, std::pair<vertex_t, vertex_t>> mp;

	for (int i = 0; i < g.size(); i++)
		for (const auto& vert : g[i])
			mp.insert({ vert.weight, {i, vert.to} });

	size_t step = 0;

	for (const auto& edge : mp) {
		if (find(uf, edge.second.first) != find(uf, edge.second.second)) {
			unionFunc(uf, edge.second.first, edge.second.second);
			displayUF(uf, step++, false, filepath);

			result[edge.second.second].push_back({ edge.second.first, edge.first });
		}

		if (step == g.size() - 1) {
			displayUF(uf, step, true, filepath);
			break;
		}
	}

	return result;
}

void example1() {
	graph g;

	g.resize(15);

	addEdge(g, 0, 1, 15);
	addEdge(g, 0, 2, 2);
	addEdge(g, 0, 3, 5);

	addEdge(g, 1, 2, 2);
	addEdge(g, 1, 4, 10);

	addEdge(g, 3, 4, 16);

	addEdge(g, 5, 6, 8);
	addEdge(g, 5, 7, 10);

	addEdge(g, 6, 8, 18);

	addEdge(g, 7, 8, 11);
	addEdge(g, 7, 9, 25);
	addEdge(g, 9, 10, 4);

	addEdge(g, 8, 10, 1);

	addEdge(g, 11, 12, 25);

	addEdge(g, 12, 13, 24);
	addEdge(g, 12, 14, 50);

	addEdge(g, 12, 14, 12);

	addEdge(g, 1, 5, 7);
	addEdge(g, 6, 11, 20);
	addEdge(g, 10, 13, 40);

	displayGraph(g, false, "example1_graph.txt");

	graph mst = kruskal(g, "example1_uf_states.txt");

	displayGraph(mst, false, "example1_mst.txt");
}

void example2() {
	graph g;

	g.resize(6);

	addDirectedEdge(g, 0, 3, 7);
	addDirectedEdge(g, 0, 1, 4);
	addDirectedEdge(g, 0, 4, 0);

	addDirectedEdge(g, 1, 3, 6);
	addDirectedEdge(g, 1, 4, 2);

	addDirectedEdge(g, 2, 5, 9);

	addDirectedEdge(g, 3, 5, 10);

	addDirectedEdge(g, 4, 5, 8);

	displayGraph(g, true, "example2_graph.txt");

	graph mst = kruskal(g, "example2_uf_states.txt");

	displayGraph(mst, false, "example2_mst.txt");
}

int main() {
	// example1();
	example2();
}