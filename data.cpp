#include "data.h"
#include <cmath>

double City::getX() const{
	return x;
}
double City::getY() const{
	return y;
}
double City::computeDistance(const City& city) const{
	if(*this == city)
		return 0;
	return std::sqrt( std::pow(city.getX() - this->getX(),2) 
			+ std::pow(city.getY() - this->getY(),2) );
}
