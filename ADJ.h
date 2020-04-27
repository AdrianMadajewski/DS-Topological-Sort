#ifndef ADJ_H
#define ADJ_H

#include <vector>	// for std::vector
#include <stack>	// for std::stack

class AdjGraph {
private:
	enum Color { WHITE, GREY, BLACK };
	enum Connection { EMPTY, CONNECTED };
	size_t V;
	size_t E;
	Connection** adj; // 2D-array
	bool DFSUtil(int vertex, std::vector<Color>& visited, std::stack<int>& stack);
public:
	AdjGraph(int vertices, int edges);
	AdjGraph(const std::vector<std::pair<int, int>>& data);
	~AdjGraph();
	void addEdge(int first, int second);
	void sortDFS();
	void sortDEL();
};

#endif // !ADJ_H
