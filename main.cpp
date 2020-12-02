#include <iostream>
#include <vector>
#include "readFromFile.hpp"
#include "RouteGraph.h"

int main(int argc, const char * argv[]) {
	//std::cout << "Filename: " << argv[1] << std::endl;

	/* ensures a file is passed as an argument */
	if (argc == 0) {
		std::cout << "Please enter a valid directory" << std::endl;
		return 2;
	}

	RouteGraph g(argv[1]);
}