#include "ADJ.h"

#include <iostream>
#include <vector>		// for std::vector
#include <stack>		// for std::stack
#include <queue>		// for std::queue

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

	// Allocate memory and set everything to EMPTY
	adj = new int* [V];
	for (int row = 0; row < V; ++row) {
		adj[row] = new int[V];
		for (int col = 0; col < V; ++col) {
			adj[row][col] = 0;
		}
	}

	// Add edges from std::pair
	for (int i = 1; i <= E; ++i) {
		addEdge(data[i].first, data[i].second);
	}
}

// Clear up the memory
AdjGraph::~AdjGraph() {
	for (int i = 0; i < V; ++i) {
		delete[] adj[i];
	}
	delete[] adj;
}

// Indexing from 0 to n - 1 
void AdjGraph::addEdge(int first, int second) {
	adj[first - 1][second - 1] = 1;
}

// Returns true if found a cycle
void AdjGraph::DFSUtil(int vertex, std::vector<Color>& visited, std::stack<int>& stack, bool &hasCycle) {
	visited[vertex] = Color::GREY;

	// For each vertex check it's connections
	for (int current = 0; current < V; ++current) {
		// Found a cycle
		if (visited[current] == Color::GREY && adj[vertex][current] == 1) {
			hasCycle = true;
			return;
		}
		else if(visited[current] == Color::WHITE && adj[vertex][current] == 1) {
			DFSUtil(current, visited, stack, hasCycle);
		}
	}

	// Mark leaved subtree of the graph as BLACK
	visited[vertex] = Color::BLACK;

	// If has no other edges to go 
	// push the current vertex to the stack
	stack.push(vertex);
}

void AdjGraph::sortDFS() {
	std::stack<int> stack;
	std::vector<Color> visited(V, Color::WHITE);

	// For each vertex check if it hasn't been visisted
	bool hasCycle = false;

	for (int vertex = 0; vertex < V; ++vertex) {
		if (visited[vertex] == Color::WHITE) {
			DFSUtil(vertex, visited, stack, hasCycle);
			if (hasCycle) {
				std::cout << "There is a cycle in the graph." << '\n';
				std::cout << "Cannot perform topological sort." << '\n';
				return;
			}
		}
	}

	// Empty the stack structure
	// + 1 because indexing from 0 
	/*
	std::cout << "DFS sort: ";
	while (!stack.empty()) {
		std::cout << stack.top() + 1 << ' ';
		stack.pop();
	}
	std::cout << '\n';
	*/
}

void AdjGraph::sortDEL() {
	// Create a vector to store indegrees of all vertices
	std::vector<int> in_degree(V, 0);

	// For each vertex calculate it's indegree
	for (int row = 0; row < V; ++row) {
		for (int col = 0; col < V; ++col) {
			if (adj[row][col] == CONNECTED) {
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

	int count_visited_vertices = 0;
	std::vector<int> sorted;

	while (!queue.empty()) {
		int dropped = queue.front();
		queue.pop();
		sorted.push_back(dropped);

		// Iterate through the connections and decrease their in-degree
		for (int vertex = 0; vertex < V; ++vertex) {
			if (adj[dropped][vertex] == CONNECTED) {
				// Add to the starting queue
				if (--in_degree[vertex] == 0) {
					queue.push(vertex);
				}
			}
		}
		++count_visited_vertices;
	}

	// If there are any vertices left there must be a cycle
	if (count_visited_vertices != V) {
		std::cout << "There is a cycle in the graph." << '\n';
		std::cout << "Cannot perform topological sort." << '\n';
		return;
	}

	/*
	std::cout << "DEL sort: ";
	for (const auto& vertex : sorted) {
		std::cout << vertex + 1 << ' ';
	}
	std::cout << '\n';
	*/
}