#include "List.h"

#include <iostream>
#include <list>		// for std::list
#include <vector>	// for std::vector
#include <stack>	// for std::stack
#include <queue>	// for std::queue

ListGraph::ListGraph(int v, int e) {
	V = v;
	E = e;
	succesors = new std::list<int>[V];
}

ListGraph::ListGraph(const std::vector<std::pair<int, int>> &data) {
	V = data[0].first;
	E = data[0].second;
	succesors = new std::list<int>[V];
	for (int i = 1; i < E; ++i) {
		this->addEdge(data[i].first, data[i].second);
	}
}

ListGraph::~ListGraph() {
	delete[] succesors;
}

void ListGraph::addEdge(int v1, int v2) {
	succesors[v1 - 1].push_back(v2 - 1);
}

void ListGraph::DFSUtil(int vertex, std::vector<bool>& visisted, std::stack<int>& stack) {
	visisted[vertex] = true;

	std::list<int>::iterator it;
	for (it = succesors[vertex].begin(); it != succesors[vertex].end(); ++it) {
		if (!visisted[*it]) {
			DFSUtil(*it, visisted, stack);
		}
	}
	stack.push(vertex);
}

void ListGraph::sortDFS() {
	std::stack<int> stack;
	std::vector<bool> visited(V, false);
	for (int vertex = 0; vertex < V; ++vertex) {
		if (!visited[vertex]) {
			DFSUtil(vertex, visited, stack);
		}
	}

	if (stack.size() != V) {
		std::cout << "There is a cycle in the graph." << '\n';
		std::cout << "Cannot do topological sort." << '\n';
		return;
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
		for (it = succesors[v].begin(); it != succesors[v].end(); it++) {
			++in_degree[*it];
		}
	}
	
	std::queue<int> queue;
	for (int v = 0; v < V; ++v) {
		if (in_degree[v] == 0)
			queue.push(v);
	}

	int count_visisted_vertices = 0;
	std::vector<int> top_order;

	while (!queue.empty()) {
		int q = queue.front();
		queue.pop();
		top_order.push_back(q);

		std::list<int>::iterator it;
		for (it = succesors[q].begin(); it != succesors[q].end(); ++it) {
			if (--in_degree[*it] == 0) {
				queue.push(*it);
			}
		}
		++count_visisted_vertices;
	}

	if (count_visisted_vertices != V) {
		std::cout << "There is a cycle in the graph." << '\n';
		std::cout << "Cannot do topological sort." << '\n';
		return;
	}

	std::cout << "DEL sort: ";
	for (const auto& vertex : top_order) {
		std::cout << vertex + 1 << ' ';
	}
	std::cout << '\n';
}