#include "ADJ.h"

#include <iostream>
#include <vector>		// for std::vector
#include <stack>		// for std::stack
#include <queue>		// for std::queue

// https://codeforces.com/blog/entry/4907

AdjGraph::AdjGraph(int v, int e) {
	V = v;
	E = e;
	adj = new int* [V];
	for (int row = 0; row < V; ++row) {
		adj[row] = new int[V];
		for (int col = 0; col < V; ++col) {
			adj[row][col] = 0;
		}
	}
}

AdjGraph::AdjGraph(const std::vector<std::pair<int, int>>& data) {
	V = data[0].first;
	E = data[0].second;

	// Allocate memory
	adj = new int* [V];
	for (int row = 0; row < V; ++row) {
		adj[row] = new int[V];
		for (int col = 0; col < V; ++col) {
			adj[row][col] = 0;
		}
	}

	for (int i = 1; i <= E; ++i) {
		addEdge(data[i].first, data[i].second);
	}
}

AdjGraph::~AdjGraph() {
	for (int i = 0; i < V; ++i) {
		delete[] adj[i];
	}
	delete[] adj;
}

/*
void AdjGraph::print() {
	for (int row = 0; row < V; row++) {
		for (int col = 0; col < V; col++) {
			std::cout << adj[row][col] << ' ';
		}
		std::cout << '\n';
	}
}
*/

// Indexing from 0 to n - 1 
void AdjGraph::addEdge(int first, int second) {
	adj[first - 1][second - 1] = 1;
}

void AdjGraph::DFSUtil(int v, std::vector<Color>& visited, std::stack<int>& stack, bool &cycle) {
	visited[v] = Color::GREY;

	for (int vertex = 0; vertex < V; ++vertex) {

		// Found a cycle
		if (visited[vertex] == Color::GREY && adj[v][vertex] == 1) {
			cycle = true;
			return;
		}
		else if(visited[vertex] == Color::WHITE && adj[v][vertex] == 1) {
			DFSUtil(vertex, visited, stack, cycle);
		}
	}

	// Mark leaved subtree of the graph as BLACK
	visited[v] = Color::BLACK;

	// If has no other edges to go push the 
	// current vertex to the stack
	stack.push(v);
}

void AdjGraph::sortDFS() {
	std::stack<int> stack;
	std::vector<Color> visited(V, Color::WHITE);

	// For each vertex check if its been visisted
	// If not do mark as visited and do a check to push it's
	// Neighbours to the stack 
	bool cycle = false;

	for (int vertex = 0; vertex < V; ++vertex) {
		if (visited[vertex] == Color::WHITE) {
			DFSUtil(vertex, visited, stack, cycle);
			if (cycle) {
				std::cout << "There is a cycle in the graph." << '\n';
				std::cout << "Cannot perform topological sort." << '\n';
				return;
			}
		}
	}

	// Empty the stack structure
	// + 1 because indexing from 0 
	std::cout << "DFS sort: ";
	while (!stack.empty()) {
		std::cout << stack.top() + 1 << ' ';
		stack.pop();
	}
	std::cout << '\n';
}

void AdjGraph::sortDEL() {
	// Create a vector to store indegrees of all vertices
	std::vector<int> in_degree(V, 0);

	// For each vertex calculate it's indegree
	for (int row = 0; row < V; ++row) {
		for (int col = 0; col < V; ++col) {
			if (adj[row][col] == 1) {
				++in_degree[col];
			}
		}
	}
	
	// Create an queue and enqueue all vertices with indegree 0
	std::queue<int> queue;
	for (int vertex = 0; vertex < V; ++vertex) {
		if (in_degree[vertex] == 0) {
			queue.push(vertex);
		}
	}

	int count_visisted_vertices = 0;
	std::vector<int> top_order;

	while (!queue.empty()) {
		int q = queue.front();
		queue.pop();
		top_order.push_back(q);

		// Iterate through the neibhbours and decrease their in-degree
		for (int vertex = 0; vertex < V; ++vertex) {
			if (adj[q][vertex]) {
				// Add to the starting queue
				if (--in_degree[vertex] == 0) {
					queue.push(vertex);
				}
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
	for (const auto& vertex : top_order) {
		std::cout << vertex + 1 << ' ';
	}
	std::cout << '\n';
}