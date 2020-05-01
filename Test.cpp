#include "Test.h"
#include "File.h"
#include "ADJ.h"
#include "GraphMatrix.h"
#include "List.h"	

#include <fstream>
#include <string>
#include <iostream>
#include <chrono>

#define UNIT_TIME std::chrono::microseconds

void perfromTesting() {
	using clock = std::chrono::high_resolution_clock;
	std::string filename = "input";
	std::string extension = ".txt";

	std::ofstream adjOutput("adj.out");
	std::ofstream listOutput("list.out");
	std::ofstream graphOutput("graph.out");

	adjOutput << "V-SIZE\tDFS-TIME\tDEL-TIME\n";
	listOutput << "V-SIZE\tDFS-TIME\tDEL-TIME\n";
	graphOutput << "V-SIZE\tDFS-TIME\tDEL-TIME\n";

	std::chrono::time_point<clock> start;
	std::chrono::time_point<clock> stop;

	for (int i = 1; i <= 100; i++) {
		std::string currentFile = filename + std::to_string(i) + extension;
		std::cout << currentFile << " STARTED" << '\n';

		auto data = loadDataFromFile(currentFile);
		int timeDFS;
		int timeDEL;

		AdjGraph adj(data);
		std::cout << "ADJ DFS STARTED" << '\n';

		start = clock::now();
		adj.sortDFS();
		stop = clock::now();

		std::cout << "ADJ DFS DONE" << '\n';
		timeDFS = std::chrono::duration_cast<UNIT_TIME>(stop - start).count();

		std::cout << "ADJ DEL STARTED" << '\n';

		start = clock::now();
		adj.sortDEL();
		stop = clock::now();

		std::cout << "ADJ DEL DONE" << '\n';
		timeDEL = std::chrono::duration_cast<UNIT_TIME>(stop - start).count();

		adjOutput << adj.V << '\t' << timeDFS << '\t' << timeDEL << '\n';

		ListGraph list(data);

		std::cout << "LIST DFS STARTED" << '\n';
		start = clock::now();
		list.sortDFS();
		stop = clock::now();
		std::cout << "LIST DFS DONE" << '\n';
		timeDFS = std::chrono::duration_cast<UNIT_TIME>(stop - start).count();

		std::cout << "LIST DEL STARTED" << '\n';
		start = clock::now();
		list.sortDEL();
		stop = clock::now();
		std::cout << "LIST DEL DONE" << '\n';
		timeDEL = std::chrono::duration_cast<UNIT_TIME>(stop - start).count();

		listOutput << list.V << '\t' << timeDFS << '\t' << timeDEL << '\n';

		GraphMatrix graph(data);

		std::cout << "GRAPH DFS STARTED" << '\n';
		start = clock::now();
		graph.sortDFS();
		stop = clock::now();
		std::cout << "GRAPH DFS DONE" << '\n';
		timeDFS = std::chrono::duration_cast<UNIT_TIME>(stop - start).count();

		std::cout << "GRAPH DEL STARTED" << '\n';
		start = clock::now();
		graph.sortDEL();
		stop = clock::now();
		std::cout << "GRAPH DEL DONE" << '\n';
		timeDEL = std::chrono::duration_cast<UNIT_TIME>(stop - start).count();

		graphOutput << graph.V << '\t' << timeDFS << '\t' << timeDEL << '\n';

		std::cout << currentFile << " ENDED" << '\n';
	}
}
