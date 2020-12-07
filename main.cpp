#include <iostream>
#include <vector>
#include "readFromFile.hpp"
#include "RouteGraph.h"
#include "Utility.h"
#include "AirportList.hpp"
#include "MapImage.h"

int main(int argc, const char * argv[]) {
	//std::cout << "Filename: " << argv[1] << std::endl;

	/* ensures a file is passed as an argument */
	if (argc != 3) {
		std::cout << "Please pass in two valid file directories as arguments" << std::endl;
		std::cout << "The first argument should be the airports file name, followed by the routes file name" << std::endl;
		return 2;
	}


	MapImage map(argv[1], argv[2]);
	map.drawAirports("out.png");

}