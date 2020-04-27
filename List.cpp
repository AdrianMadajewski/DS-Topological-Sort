#include "List.h"

#include <iostream>
#include <list>		// for std::list
#include <vector>	// for std::vector
#include <stack>	// for std::stack
#include <queue>	// for std::queue

ListGraph::ListGraph(int v, int e) {
	V = v;
	E = e;
	succ = new std::list<int>[V];
}

ListGraph::ListGraph(const std::vector<std::pair<int, int>> &data) {
	V = data[0].first;
	E = data[0].second;
	succ = new std::list<int>[V];
	for (int i = 1; i <= E; ++i) {
		addEdge(data[i].first, data[i].second);
	}
}

ListGraph::~ListGraph() {
	delete[] succ;
}

void ListGraph::addEdge(int first, int second) {
	succ[first - 1].push_back(second - 1);
}

// Returns true if found a cycle
bool ListGraph::DFSUtil(int vertex, std::vector<Color>& visited, std::stack<int>& stack) {
	visited[vertex] = Color::GREY;

	// No cycle assumed
	bool returnValue = false;

	std::list<int>::iterator it;
	for (it = succ[vertex].begin(); it != succ[vertex].end(); ++it) {
		// Found cycle
		if (visited[*it] == Color::GREY) {
			returnValue = true;
		}
		else if (visited[*it] == Color::WHITE) {
			returnValue = DFSUtil(*it, visited, stack);
		}
	}
	// Mark leaved subtree of the graph as BLACK
	visited[vertex] = Color::BLACK;

	// If has no other edges to go 
	// push the current vertex to the stack
	stack.push(vertex);

	return returnValue;
}

void ListGraph::sortDFS() {
	std::stack<int> stack;
	std::vector<Color> visited(V, Color::WHITE);
	for (int vertex = 0; vertex < V; ++vertex) {
		if (visited[vertex] == Color::WHITE) {
			if (DFSUtil(vertex, visited, stack)) {
				std::cout << "There is a cycle in the graph." << '\n';
				std::cout << "Cannot perform topological sort." << '\n';
				return;
			}
		}
	}

	std::cout << "DFS sort: ";
	while (!stack.empty()) {
		std::cout << stack.top() + 1 << ' ';
		stack.pop();
	}
	std::cout << '\n';
}

void ListGraph::sortDEL() {
	std::vector<int> in_degree(V, 0);

	// Traverse the list to fill in-degree of each vertex
	for (int v = 0; v < V; ++v) {
		std::list<int>::iterator it;
		for (it = succ[v].begin(); it != succ[v].end(); it++) {
			++in_degree[*it];
		}
	}
	
	// Queue up vertices with in-degree 0 
	std::queue<int> queue;
	for (int v = 0; v < V; ++v) {
		if (in_degree[v] == 0)
			queue.push(v);
	}

	int count_visisted_vertices = 0;
	std::vector<int> sorted;

	while (!queue.empty()) {
		int q = queue.front();
		queue.pop();
		sorted.push_back(q);

		// For all succesors decrease it's in-degrees
		std::list<int>::iterator it;
		for (it = succ[q].begin(); it != succ[q].end(); ++it) {
			if (--in_degree[*it] == 0) {
				queue.push(*it); // <- If has no incoming edges queue it up
			}
		}
		++count_visisted_vertices;
	}

	if (count_visisted_vertices != V) {
		std::cout << "There is a cycle in the graph." << '\n';
		std::cout << "Cannot perform topological sort." << '\n';
		return;
	}

	std::cout << "DEL sort: ";
	for (const auto& vertex : sorted) {
		std::cout << vertex + 1 << ' ';
	}
	std::cout << '\n';
}