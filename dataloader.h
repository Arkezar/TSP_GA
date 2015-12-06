#ifndef DL_H
#define DL_H
#include <string>
#include <vector>
#include <unordered_map>
#include "data.h"

struct pairhash {
	public:
		size_t operator()(std::pair<City,City> key) const{
			return std::hash<double>()(key.first.getX()) ^
				std::hash<double>()(key.first.getY()) ^
				std::hash<double>()(key.second.getX()) ^
				std::hash<double>()(key.second.getY());
		}
};

std::vector<City> loadDataFromFile(const std::string&);
std::unordered_map< std::pair<City,City>, double,  pairhash > 
	createDistanceMatrix(const std::vector<City>&);
#endif
