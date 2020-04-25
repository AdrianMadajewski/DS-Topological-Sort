#ifndef LIST_H
#define LIST_H

#include <list>		// for std::list
#include <vector>	// for std::vector
#include <stack>	// for std::stack
#include <utility>	// for std::pair



class ListGraph {
private:
	enum class Color { WHITE, GREY, BLACK, };
	size_t V;
	size_t E;
	std::list<int>* succ;	// Pointer to std::list
	void DFSUtil(int v, std::vector<Color>& visisted, std::stack<int>& stack, bool &cycle);
public:
	ListGraph(int v, int e);
	ListGraph(const std::vector<std::pair<int, int>> &data);
	~ListGraph();
	void addEdge(int v1, int v2);
	void sortDFS();
	void sortDEL();
};

#endif // !LIST_H
