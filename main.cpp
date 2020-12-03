

#include <iostream>
#include <vector>
#include "readFromFile.hpp"
#include "RouteGraph.h"
#include "Utility.h"

int main(int argc, const char * argv[]) {
	//std::cout << "Filename: " << argv[1] << std::endl;

	/* ensures a file is passed as an argument */
	if (argc == 0) {
		std::cout << "Please enter a valid directory" << std::endl;
		return 2;
	}

	Util util;
	double dist = util.distance(std::pair<double, double>(1.0, 1.0), std::pair<double, double>(1.0, 1.0));
	std::cout << "test distance is " << dist << std::endl;

	RouteGraph g(argv[1]);
	vector<RouteDistance> v = g.getAllRoutes();

	std::cout << v.size() << std::endl;

}