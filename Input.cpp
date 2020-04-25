#include "Input.h"

#include <string>	// for std::string
#include <vector>	// for std::vector
#include <utility>	// for std::pair
#include <iostream>

int getUserInput(const std::string& message) {
	if (!message.empty())
		std::cout << message << '\n';

	while (true) {
		int x{};
		std::cin >> x;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Invalid input - please try again." << '\n';
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return x;
		}
	}
}

int getUserDataSize(const std::string& message) {
	if (!message.empty()) {
		std::cout << message << '\n';
	}

	while (true) {
		int x{ getUserInput() };
		if (x >= 1)
			return x;
		else
			std::cerr << "Invalid input - must be greater than 0." << '\n';
	}
}

int getUserVertex(int v_max, const std::string& message) {
	if (!message.empty()) {
		std::cout << message << '\n';
	}

	while (true) {
		int x{ getUserInput() };
		if (x > 0 && x <= v_max) {
			return x;
		}
		else {
			std::cerr << "Invalid input - out of vertices range." << '\n';
		}
	}
}

std::vector<std::pair<int, int>> getUserPairs(const std::string& message) {
	if (!message.empty()) {
		std::cout << message << '\n';
	}

	int v = getUserDataSize("Enter number of vertices: ");
	int e = getUserDataSize("Enter number of edges: ");

	auto pair = std::make_pair(v, e);

	std::vector<std::pair<int, int>> result{ pair };

	for (int i = 0; i < e; ++i) {
		std::pair<int, int> pair;
		std::cout << i + 1 << " -> v1: ";
		int v1 = getUserVertex(v);
		std::cout << i + 1 << " -> v2: ";
		int v2 = getUserVertex(v);
		pair = std::make_pair(v1, v2);
		result.emplace_back(pair);
	}
	return result;
}