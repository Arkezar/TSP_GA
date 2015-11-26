#include "genetic.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <algorithm>

std::vector<City> generateRandomCandidate(std::vector<City> cities){
	std::srand(std::time(0));

	std::vector<City> resultingCandidate;
	while(cities.size() > 0){
		auto tmp = cities.at( std::rand() % cities.size() ); 
		resultingCandidate.push_back(tmp);
		cities.erase( std::find( cities.begin(), cities.end()-1, tmp ) );
	}
	return resultingCandidate;
}
