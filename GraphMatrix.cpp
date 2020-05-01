#include "GraphMatrix.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

GraphMatrix::GraphMatrix() {}

GraphMatrix::GraphMatrix(const std::vector<std::pair<int, int>>& data) {
	V = data[0].first;
	E = data[0].second;

	// Allocate memory from 1 to V and V + 5
	matrix = new int* [V + 1];
	for (int row = 1; row < V + 1; ++row) {
		matrix[row] = new int[V + 4];
		for (int col = 1; col < V + 4; ++col) {
			matrix[row][col] = 0;
		}
	}

	succ = new std::list<int>[V + 1];
	pred = new std::list<int>[V + 1];
	// noInc = new std::list<int>[V + 1];

	first_succ_col = V + 1;
	first_pred_col = V + 2;
	// first_no_inc_col = V + 3;

	// Add all the vertices to noIncidence list
	/*
	for (int v = 1; v <= V; ++v) {
		for (int w = 1; w <= V; ++w) {
			noInc[v].push_back(w);
		}
	}
	*/

	for (int i = 1; i <= E; ++i) {
		addSuccesor(data[i].first, data[i].second);
		addPredecessor(data[i].first, data[i].second);
		// removeIncidenced(data[i].first, data[i].second);
	}

	for (int v = 1; v <= V; ++v) {
		succ[v].sort();
		pred[v].sort();
		// noInc[v].sort();
	}

	for (int vertex = 1; vertex <= V; ++vertex) {
		matrix[vertex][first_succ_col] = getMinElement(succ[vertex]);
		matrix[vertex][first_pred_col] = getMinElement(pred[vertex]);
		// matrix[vertex][first_no_inc_col] = getMinElement(noInc[vertex]);

		std::list<int>::iterator it;
		for (it = succ[vertex].begin(); it != succ[vertex].end(); ++it) {
			matrix[vertex][*it] = succ[vertex].back();
		}
		for (it = pred[vertex].begin(); it != pred[vertex].end(); ++it) {
			matrix[vertex][*it] = pred[vertex].back() + V;
		}
		/*for (it = noInc[vertex].begin(); it != noInc[vertex].end(); ++it) {
			matrix[vertex][*it] = noInc[vertex].back() * -1;
		}
		*/
	}
}

GraphMatrix::~GraphMatrix() {
	for (int i = 1; i <= V; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] succ;
	delete[] pred;
	// delete[] noInc;
}

void GraphMatrix::addSuccesor(int first, int second) {
	succ[first].push_back(second);
}

void GraphMatrix::addPredecessor(int first, int second) {
	pred[second].push_back(first);
}

void GraphMatrix::removeIncidenced(int first, int second) {
	// noInc[first].remove(second);
	// noInc[second].remove(first);
}

void GraphMatrix::DFSUtil(int vertex, std::vector<Color> &visited, std::stack<int> &stack, bool &hasCycle) {
	visited[vertex] = GREY;

	for (int current = 1; current <= V; ++current) {	
		if (matrix[vertex][current] > 0 && matrix[vertex][current] <= V && visited[current] == GREY) {
			hasCycle = true;
			return;
		}
		else if (matrix[vertex][current] > 0 && matrix[vertex][current] <= V && visited[current] == WHITE) {
			DFSUtil(current, visited, stack,hasCycle);
		}
	}

	visited[vertex] = BLACK;
	stack.push(vertex);
}

void GraphMatrix::sortDFS() {
	std::vector<Color> visited(V + 1, WHITE);
	std::stack<int> stack;

	bool hasCycle = false;

	for (int vertex = 1; vertex <= V; ++vertex) {
		if (visited[vertex] == WHITE) {
			DFSUtil(vertex, visited, stack, hasCycle);
			if (hasCycle) {
				std::cout << "There is a cycle in the graph." << '\n';
				std::cout << "Cannot perform topological sort." << '\n';
				return;
			}
		}
	}

	/*
	std::cout << "DFS sort: ";
	while (!stack.empty()) {
		std::cout << stack.top() << ' ';
		stack.pop();
	}
	std::cout << '\n';
	*/
}

int GraphMatrix::getMinElement(std::list<int>& data) {
	if (!data.size()) {
		return 0;
	}
	return data.front();
}

void GraphMatrix::printMatrix() {
	for (int row = 1; row < V + 1; ++row) {
		for (int col = 1; col < V + 4; ++col) {
				std::cout << matrix[row][col] << '\t';
		}
		std::cout << '\n';
	}
}

void GraphMatrix::sortDEL() {
	std::vector<int> in_degree(V + 1, 0);

	for (int v = 1; v <= V; ++v) {
		std::list<int>::iterator it;
		for (it = succ[v].begin(); it != succ[v].end(); it++) {
			++in_degree[*it];
		}
	}

	std::queue<int> queue;
	for (int v = 1; v <= V; ++v) {
		if (in_degree[v] == 0) {
			queue.push(v);
		}
	}

	int count_visited_vertices = 0;
	std::vector<int> sorted;

	while (!queue.empty()) {
		int dropped = queue.front();
		queue.pop();
		sorted.push_back(dropped);
		
		std::list<int>::iterator it;
		for (it = succ[dropped].begin(); it != succ[dropped].end(); ++it) {
			if (--in_degree[*it] == 0) {
				queue.push(*it); // <- If has no incoming edges queue it up
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
		std::cout << vertex << ' ';
	}
	std::cout << '\n';
	*/
}