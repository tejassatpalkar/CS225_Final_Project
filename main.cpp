#include <iostream>
#include <vector>
#include "readFromFile.hpp"
#include "RouteGraph.h"
#include "Utility.h"
#include "AirportList.hpp"

int main(int argc, const char * argv[]) {
	//std::cout << "Filename: " << argv[1] << std::endl;

	/* ensures a file is passed as an argument */
	if (argc != 3) {
		std::cout << "Please pass in two valid file directories as arguments" << std::endl;
		std::cout << "The first argument should be the airports file name, followed by the routes file name" << std::endl;
		return 2;
	}

	/* create the airport list */
	AirportList al(argv[1]);

	/* create the route graph and pass in the airport list */
	RouteGraph g(argv[2], al);

	
	vector<RouteDistance> v = g.getAllRoutes();

	std::cout << v.size() << std::endl;

}