#include "dataloader.h"
#include "data.h"
#include <stdexcept>
#include <fstream>
#include <memory>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cstdlib>

std::vector<City> loadDataFromFile(const std::string& filePath){
	std::ifstream dataFile(filePath);
	std::string line;
	std::vector<City> cityVector;
	bool readCityCoords = false;
	while(std::getline(dataFile, line)){
		if((line) == "TOUR_SECTION")
			readCityCoords = false;
		if(readCityCoords){
			std::vector<std::string> tokens;
			std::istringstream iss(line);
			std::copy(std::istream_iterator<std::string>(iss), 
				std::istream_iterator<std::string>(),
				std::back_inserter(tokens));
			cityVector.push_back( City(std::stoi(tokens.at(1)),
						std::stoi(tokens.at(2))) );
		}
		if((line) == "NODE_COORD_SECTION")
			readCityCoords = true;
	}
	return cityVector;
}

std::unordered_map< std::pair<City,City>, double, pairhash > 
	createDistanceMatrix(const std::vector<City>& cityCoordinatesVector){
		std::unordered_map< std::pair<City,City>, double, pairhash > matrix;
		for(const auto& c1 : cityCoordinatesVector){
			for(const auto& c2 : cityCoordinatesVector){
				matrix.emplace(std::make_pair(std::make_pair(c1,c2), c1.computeDistance(c2)) );
			}
		}
		return matrix;
	}
