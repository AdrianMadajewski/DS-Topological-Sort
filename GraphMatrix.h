#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <vector>	// for std::vector
#include <utility>	// for std::pair
#include <list>		// for std::list
#include <stack>

class GraphMatrix {
public:
	GraphMatrix();
	GraphMatrix(const std::vector<std::pair<int, int>>& data);
	~GraphMatrix();
	void printMatrix();
	void sortDFS();
	void sortDEL();

	size_t V;
	size_t E;
private:
	enum Color { WHITE, GREY, BLACK };
	
	int first_succ_col;
	int first_pred_col;
	int first_no_inc_col;

	int** matrix;
	std::list<int>* succ;
	std::list<int>* pred;
	// std::list<int>* noInc;
	void removeIncidenced(int first, int second);
	int getMinElement(std::list<int>& data);
	void addSuccesor(int first, int second);
	void addPredecessor(int first, int second);
	void DFSUtil(int vertex, std::vector<Color>& visited, std::stack<int> &stack, bool &hasCycle);
};

#endif // !GRAPH_MATRIX_H