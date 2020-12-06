#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>


#include "../catch/catch.hpp"
#include "../readFromFile.hpp"
#include "../Utility.h"
#include "../RouteGraph.h"

using std::string;
using std::vector;
using std::unordered_map;

TEST_CASE("Verify that file_to_string works on a small example") {
	std::string res = file_to_string("tests/smallSample.txt");
	// always check "expected" == "actual" --> be consistent
	REQUIRE("hello\nstudents\nof\ncs\n225\n!!!\n" == res);
}

TEST_CASE("Verify that file_to_vector works on a small example") {
	std::vector<std::string> res = file_to_vector("tests/smallSample.txt");
	std::string expected[] = {"hello", "students", "of", "cs", "225", "!!!"};
	
	REQUIRE(6 == res.size());

	for (int i = 0; i < res.size(); i++) {
		REQUIRE(expected[i] == res[i]);
	}
}		

TEST_CASE("Verify that Utility Class Distance function works") {
	std::vector<std::string> data = file_to_vector("test_coordinates_distances.csv");

	std::vector<double> solutions{3039.15,1117.83, 12656.4, 9220.13, 2981.89};
	std::pair<double,double> p1(33.63100052,-85.15200043);
	std::pair<double,double> p2(40.06639862,-118.5650024);
	std::pair<double,double> p3(53.31919861,-117.7529984);
	std::pair<double,double> p4(52.12060165,-101.2360001);
	std::pair<double,double> p5(33.36569977,-84.16519928);
	std::pair<double,double> p6(-15.50500011,167.2200012);
	std::pair<double,double> p7(52.19549942,21.65589905);
	std::pair<double,double> p8(29.52969933,-98.279);
	std::pair<double,double> p9(26.75460052,55.90240097);
	std::pair<double,double> p10(23.31430054,85.32170105);

	

	REQUIRE(((distance(p1,p2) <= solutions[0] + solutions[0]*0.05) && (distance(p1,p2) >= solutions[0] - solutions[0]*0.05)));
	REQUIRE(((distance(p3,p4) <= solutions[1] + solutions[1]*0.05) && (distance(p3,p4) >= solutions[1] - solutions[1]*0.05)));
	REQUIRE(((distance(p5,p6) <= solutions[2] + solutions[2]*0.05) && (distance(p5,p6) >= solutions[2] - solutions[2]*0.05)));
	REQUIRE(((distance(p7,p8) <= solutions[3] + solutions[3]*0.05) && (distance(p7,p8) >= solutions[3] - solutions[3]*0.05)));
	REQUIRE(((distance(p9,p10) <= solutions[4] + solutions[4]*0.05) && (distance(p9,p10) >= solutions[4] - solutions[4]*0.05)));
}


TEST_CASE("Validate the Creation of a RouteGraph", "[RouteGraph]") {

	/* constant values validated in Python 
	   notebook: https://jovian.ai/nishantbalepur/cs225-test */
	const int NUM_EDGES = 37505;
	const int NUM_VERTICES = 3334;

	/* objects to test */
	AirportList al("data/airports.dat");
	RouteGraph rg("data/routes.dat", al);
	Graph graph = rg.getGraph();

	/* sanity check for the number of airports and connections in the graph */
	SECTION("Verify number of edges and vertices") {
		REQUIRE(rg.getNumAirports() == NUM_VERTICES);
		REQUIRE(rg.getNumConnections() == NUM_EDGES);
	}

	/* check existence/nonexistence of random airports */
	SECTION("Check airport existence/nonexistence") {
		REQUIRE(graph.vertexExists("2816"));
		REQUIRE(graph.vertexExists("6173"));
		REQUIRE(graph.vertexExists("140"));

		REQUIRE(!graph.vertexExists("0000"));
		REQUIRE(!graph.vertexExists("thiswontexist"));
	}

	/* check existence/nonexistence of random connections */
	SECTION("Check connection existence/nonexistence") {
		REQUIRE(graph.edgeExists("7238", "7240"));
		REQUIRE(graph.edgeExists("3382", "3395"));
		REQUIRE(graph.edgeExists("1456", "345"));
		
		REQUIRE(!graph.edgeExists("-12", "0.5"));
		REQUIRE(!graph.edgeExists("1452", "1452"));
	}

	/* check weights of random connections */
	SECTION("Check distance between airports") {

		REQUIRE(graph.getEdgeWeight("1037", "1020") == (int) distance(pair<float, float>(-2.91917991638, 25.915399551399997),
																	  pair<float, float>(-4.38575, 15.4446)));

		REQUIRE(graph.getEdgeWeight("5461", "304") == (int) distance(pair<float, float>(54.1796989440918, -58.45750045776367),
																	  pair<float, float>(50.459202, 4.45382)));
	}
}

TEST_CASE("Validate BFS Traversal of a RouteGraph", "[RouteGraph]") {

	/* objects to test */
	AirportList al("data/airports.dat");
	RouteGraph rg("data/routes.dat", al);
	Graph graph = rg.getGraph();

	vector<RouteDistance> routes = rg.getAllRoutes();

	/* ensures every edge was traversed */
	SECTION("BFS sanity check") {
		/* compares the sizes of the edges and the number of routes in BFS */
		REQUIRE((int) routes.size() == rg.getNumConnections());
	}

	/* ensures every connection and weight is accurate */
	SECTION("Validate connections and weights") {
		/* iterates through every RouteDistane */
		for (const RouteDistance& rd : routes) {
			/* gets the current route and weight */
			Route route = rd.first;
			int weight = rd.second;

			/* checks that the edge exists */
			REQUIRE(graph.edgeExists(route.first, route.second));

			/* validates the distance of the route */
			REQUIRE(weight == graph.getEdgeWeight(route.first, route.second));
		}
	}

	/* checks for duplicates */
	SECTION("No duplicates in BFS") {
		/* intialize variables*/
		unordered_map<string, bool> duplicates = unordered_map<string, bool>();
		bool noDuplicates = true;

		/* iterates through each route */
		for (const RouteDistance& rd : routes) {
			/* create a string representation of the object */
			string repr = rd.first.first + "~" + rd.first.second + "~" + to_string(rd.second);

			/* check if the item exists in the map */
			if (duplicates.find(repr) != duplicates.end()) {
				noDuplicates = false;
				break;
			}

			/* add to the map */
			duplicates[repr] = true;
		}

		/* require the boolean state */
		REQUIRE(noDuplicates);
	}
}



