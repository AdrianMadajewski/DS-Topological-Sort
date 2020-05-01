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

int getUserVerticesSize(const std::string& message) {
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

int getUserVertex(int vMaxCapacity, const std::string& message) {
	if (!message.empty()) {
		std::cout << message << '\n';
	}

	while (true) {
		int x{ getUserInput() };
		if (x > 0 && x <= vMaxCapacity) {
			return x;
		}
		else {
			std::cerr << "Invalid input - out of vertices range." << '\n';
		}
	}
}

int getUserEdgesSize(int vMaxCapacity, const std::string& message) {
	if (!message.empty()) {
		std::cout << message << '\n';
	}

	const int eMaxCapacity = (vMaxCapacity * (vMaxCapacity - 1));
	while (true) {
		int x{ getUserInput() };
		if (x > 0 && x <= eMaxCapacity) {
			return x;
		}
		else {
			std::cerr << "Invalid input - out of edges range. (max: " << eMaxCapacity << ")" << '\n';
			std::cerr << "Maximum number of edges must be V(V-1) for directed graph" << '\n';
		}
	}
}

std::vector<std::pair<int, int>> getUserPairs(const std::string& message) {
	if (!message.empty()) {
		std::cout << message << '\n';
	}

	int v = getUserVerticesSize("Enter number of vertices: ");
	int e = getUserEdgesSize(v, "Enter number of edges: ");
	auto pair = std::make_pair(v, e);
	std::vector<std::pair<int, int>> result{ pair };

	for (int i = 0; i < e; ++i) {
		std::cout << i + 1 << " -> v1: ";
		auto v1 = getUserVertex(v);
		std::cout << i + 1 << " -> v2: ";
		auto v2 = getUserVertex(v);
		result.emplace_back(std::make_pair(v1, v2));
	}
	return result;
}

bool askUserIf(const std::string& message)
{
	if (!message.empty())
		std::cout << message << '\n';

	while (true)
	{
		int x{ getUserInput() };
		switch (x)
		{
		case 0:
			return false;
		case 1:
			return true;
		default:
			std::cerr << "Invalid input - please try again." << '\n';
			break;
		}
	}
}