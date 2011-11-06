#include "route.hh"
#include "../vertex.hh"
#include "../rules.hh"

Route::Route(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	corners[NE]=ne;
	corners[SE]=se;
	corners[SW]=sw;
	corners[NW]=nw;
	std::cout << this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Route* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Route& r) {
	return os << "Route " << r.corners[NE] << "-" << r.corners[SE] << "-" << r.corners[NW] << "-" << r.corners[SW];
}
