#ifndef LIST_H
#define LIST_H

#include <list>		// for std::list
#include <vector>	// for std::vector
#include <stack>	// for std::stack
#include <utility>	// for std::pair

class ListGraph {
private:
	enum Color { WHITE, GREY, BLACK, };
	std::list<int>* succ;	// Pointer to std::list
	void DFSUtil(int vertex, std::vector<Color>& visisted, std::stack<int>& stack, bool &hasCycle);
public:
	size_t V;
	size_t E;
	ListGraph(int vertices, int edges); // this is useless for now
	ListGraph(const std::vector<std::pair<int, int>> &data);
	~ListGraph();
	void sortDFS();
	void sortDEL();
	void addEdge(int first, int second);	// this should be private?
};

#endif // !LIST_H
