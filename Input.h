#ifndef INPUT_H
#define INPUT_H

#include <string>	// for std::string
#include <vector>	// for std::vector
#include <utility>	// for std::pair

int getUserInput(const std::string& message = "");
int getUserVerticesSize(const std::string& message = "");
int getUserEdgesSize(int vMaxCapacity, const std::string& message = "");
int getUserVertex(int vMaxCapacity, const std::string& message = "");
std::vector<std::pair<int, int>> getUserPairs(const std::string& message = "");

#endif // !INPUT_H