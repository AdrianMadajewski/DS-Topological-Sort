#ifndef LIST_H
#define LIST_H

#include <list>		// for std::list
#include <vector>	// for std::vector
#include <stack>	// for std::stack
#include <utility>	// for std::pair

class ListGraph {
private:
	size_t V;
	size_t E;

	// Pointer to std::list
	std::list<int>* succesors;
	void DFSUtil(int v, std::vector<bool>& visisted, std::stack<int>& stack);
public:
	ListGraph(int v, int e);
	ListGraph(const std::vector<std::pair<int, int>> &data);
	~ListGraph();
	void addEdge(int v1, int v2);
	void sortDFS();
	void sortDEL();
};

#endif // !LIST_H
