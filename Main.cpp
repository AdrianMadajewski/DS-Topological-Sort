#include <iostream>

#include "ADJ.h"
#include "List.h"
#include "GraphMatrix.h"
#include "Input.h"
#include "File.h"
// #include "Time.h"
#include "TEST.h"

int main()
{
	/*

	if (askUserIf("Enter user data? : 1 = yes, 0 = no")) {
		const auto data = getUserPairs();
		std::cout << '\n';
		std::cout << "Adjacency matrix: " << '\n';
		AdjGraph G1(data);

		// t = new Timer();
		G1.sortDFS();
		// delete t;

		// t = new Timer();
		G1.sortDEL();
		// delete t;

		std::cin.get();
		std::cout << '\n';

		std::cout << "List of successors: " << '\n';
		ListGraph G2(data);

		// t = new Timer();
		G2.sortDFS();
		// delete t;

		// t = new Timer();
		G2.sortDEL();
		// delete t;

		std::cin.get();
		std::cout << '\n';

		std::cout << "Graph matrix: " << '\n';
		GraphMatrix G3(data);
		G3.printMatrix();

		// t = new Timer();
		G3.sortDFS();
		// delete t;

		// t = new Timer();
		G3.sortDEL();
		// delete t;

		std::cin.get();
		system("cls");
	}
	if (askUserIf("Enter file data? : 1 = yes, 0 = no")) {
		std::string filename;
		std::cout << "Enter a filename: ";
		std::cin >> filename;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		const auto fileData = loadDataFromFile(filename);

		std::cout << '\n';
		std::cout << "Adjacency matrix: " << '\n';
		AdjGraph G1(fileData);
		//t = new Timer();
		G1.sortDFS();
		//delete t;

		//t = new Timer();
		G1.sortDEL();
		//delete t;

		std::cin.get();
		std::cout << '\n';

		std::cout << "List of successors: " << '\n';
		ListGraph G2(fileData);

		//t = new Timer();
		G2.sortDFS();
		//delete t;

		//t = new Timer();
		G2.sortDEL();
		//delete t;

		std::cin.get();
		std::cout << '\n';

		std::cout << "Graph matrix: " << '\n';
		GraphMatrix G3(fileData);

		//t = new Timer();
		G3.sortDFS();
		//delete t;

		//t = new Timer();
		G3.sortDEL();
		//delete t;
	}
	*/

	perfromTesting();

	return 0;
}