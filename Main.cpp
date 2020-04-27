#include <iostream>

#include "ADJ.h"
#include "List.h"
#include "GraphMatrix.h"
#include "Input.h"
#include "File.h"

// https://www.hackerearth.com/practice/algorithms/graphs/topological-sort/tutorial/
// https://codeforces.com/blog/entry/4907

int main()
{
	const auto test = loadDataFromFile("input1.txt");
	
	ListGraph a(test);
	AdjGraph b(test);
	GraphMatrix c(test);

	a.sortDFS();
	b.sortDFS();
	c.printMatrix();
	c.sortDFS();

	return 0;
}