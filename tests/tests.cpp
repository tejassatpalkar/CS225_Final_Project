#include <string>
#include <vector>


#include "../catch/catch.hpp"
#include "../readFromFile.hpp"
#include "../Utility.h"



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
	Util u;

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

	

	REQUIRE(((u.distance(p1,p2) <= solutions[0] + solutions[0]*0.05) && (u.distance(p1,p2) >= solutions[0] - solutions[0]*0.05)));
	REQUIRE(((u.distance(p3,p4) <= solutions[1] + solutions[1]*0.05) && (u.distance(p3,p4) >= solutions[1] - solutions[1]*0.05)));
	REQUIRE(((u.distance(p5,p6) <= solutions[2] + solutions[2]*0.05) && (u.distance(p5,p6) >= solutions[2] - solutions[2]*0.05)));
	REQUIRE(((u.distance(p7,p8) <= solutions[3] + solutions[3]*0.05) && (u.distance(p7,p8) >= solutions[3] - solutions[3]*0.05)));
	REQUIRE(((u.distance(p9,p10) <= solutions[4] + solutions[4]*0.05) && (u.distance(p9,p10) >= solutions[4] - solutions[4]*0.05)));

	 




}



