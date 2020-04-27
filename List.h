#ifndef LIST_H
#define LIST_H

#include <list>		// for std::list
#include <vector>	// for std::vector
#include <stack>	// for std::stack
#include <utility>	// for std::pair

class ListGraph {
private:
	enum Color { WHITE, GREY, BLACK, };
	size_t V;
	size_t E;
	std::list<int>* succ;	// Pointer to std::list
	bool DFSUtil(int vertex, std::vector<Color>& visisted, std::stack<int>& stack);
public:
	ListGraph(int vertices, int edges); // this is useless for now
	ListGraph(const std::vector<std::pair<int, int>> &data);
	~ListGraph();
	void sortDFS();
	void sortDEL();
	void addEdge(int first, int second);	// this should be private?
};

#endif // !LIST_H
