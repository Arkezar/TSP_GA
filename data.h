#ifndef City_H
#define City_H
#include <iostream>
class City{
	private:
		int x;
		int y;
	public:
		City(int x, int y):x(x),y(y){};
		
		double computeDistance(const City&) const;
		int getX() const;
		int getY() const;
};
static bool operator==(const City& lhs, const City& rhs){
	return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
};
static std::ostream& operator<<(std::ostream& out, const City& c){
			out << "City " << c.getX() << " " << c.getY();
			return out;
		}
#endif
