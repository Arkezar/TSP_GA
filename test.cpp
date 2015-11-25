
#include "data.h"
#include "dataloader.h"
#include <catch.hpp>
#include <iostream>

TEST_CASE("City creation", "[city]"){
	City c1(1,1);
	REQUIRE(c1.getX() == 1);
	REQUIRE(c1.getY() == 1);
}
TEST_CASE("City distance computation", "[city]"){
	City c1(0,0);
	City c2(2,0);
	City c3(0,2);
	REQUIRE(c1.computeDistance(c2) == 2.0);
	REQUIRE(c1.computeDistance(c3) == 2.0);
}

TEST_CASE("Loading data from file", "[data_loader]"){
	std::string fpath("att48.tsp");
	auto cityVector = loadDataFromFile(fpath);
	REQUIRE(cityVector.size() > 0);
}

TEST_CASE("Computing distance matrix", "[data_loader]"){
	std::string fpath("att48.tsp");
	auto cityVector = loadDataFromFile(fpath);
	auto distMatrix = createDistanceMatrix(cityVector);
	std::cout << distMatrix.size() << std::endl;
	double tmpDist = distMatrix.at(std::make_pair(cityVector.at(0),cityVector.at(1)));
	REQUIRE(cityVector.size() > 0);
	REQUIRE(tmpDist == 0);
}
