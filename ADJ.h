#ifndef ADJ_H
#define ADJ_H

#include <vector>	// for std::vector
#include <stack>	// for std::stack

enum Color {
	WHITE,
	GREY,
	BLACK,
};

class AdjGraph {
private:
	size_t V;
	size_t E;
	int** adj; // 2D-array
	void DFSUtil(int v, std::vector<Color>& visited, std::stack<int>& stack, bool &flag);
public:
	AdjGraph(int v, int e);
	AdjGraph(const std::vector<std::pair<int, int>>& data);
	~AdjGraph();
	void addEdge(int first, int second);
	void sortDFS();
	void sortDEL();
	void print();
};

#endif // !ADJ_H
