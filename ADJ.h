#ifndef ADJ_H
#define ADJ_H

#include <vector>	// for std::vector
#include <stack>	// for std::stack

class AdjGraph {
private:
	enum Color { WHITE, GREY, BLACK };
	enum Connection { EMPTY, CONNECTED };
	int** adj; // 2D-array
	void DFSUtil(int vertex, std::vector<Color>& visited, std::stack<int>& stack, bool &hasCycle);
public:
	size_t V;
	size_t E;
	AdjGraph(int vertices, int edges);
	AdjGraph(const std::vector<std::pair<int, int>>& data);
	~AdjGraph();
	void addEdge(int first, int second);
	void sortDFS();
	void sortDEL();
};

#endif // !ADJ_H
