#ifndef City_H
#define City_H
#include <iostream>
class City{
	private:
		double x;
		double y;
	public:
		City(double x, double y):x(x),y(y){};
		City(){
			x = -1;
			y = -1;
		};
		double computeDistance(const City&) const;
		double getX() const;
		double getY() const;
};
static bool operator==(const City& lhs, const City& rhs){
	return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
};
inline std::ostream& operator<<(std::ostream& out, const City& c){
			out << "City " << c.getX() << " " << c.getY();
			return out;
		}
#endif
