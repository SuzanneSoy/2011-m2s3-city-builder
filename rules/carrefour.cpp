#include "carrefour.hh"

Carrefour::Carrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	corners[NE]=ne;
	corners[SE]=se;
	corners[SW]=sw;
	corners[NW]=nw;
	std::cout << this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Carrefour* c) {
	return os << *c;
}

std::ostream& operator<<(std::ostream& os, const Carrefour& c) {
	return os << "Carrefour " << c.corners[NE] << "-" << c.corners[SE] << "-" << c.corners[NW] << "-" << c.corners[SW];
}
