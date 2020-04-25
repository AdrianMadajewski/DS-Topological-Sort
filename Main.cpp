#include <iostream>

#include "ADJ.h"
#include "List.h"
#include "Input.h"
#include "File.h"

// https://www.hackerearth.com/practice/algorithms/graphs/topological-sort/tutorial/

int main()
{
	const auto test = getUserPairs();
	AdjGraph a(test);
	ListGraph b(test);

	std::cout << "adj: "; a.sortDFS();
	std::cout << "adj: "; a.sortDEL();

	std::cout << "list: "; b.sortDFS();
	std::cout << "list: "; b.sortDEL();

	return 0;
}