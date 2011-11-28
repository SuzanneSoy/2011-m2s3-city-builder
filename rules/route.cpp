#include "route.hh"
#include "../vertex.hh"
#include "../directions.hh"

Route::Route(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	corners[NE]=ne;
	corners[SE]=se;
	corners[SW]=sw;
	corners[NW]=nw;
	std::cout << this << std::endl;
}

void Route::subdivide() {
	// TODO
}

std::ostream& operator<<(std::ostream& os, const Route* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Route& r) {
	return os << "Route " << r.corners[NE] << "-" << r.corners[SE] << "-" << r.corners[NW] << "-" << r.corners[SW];
}

void Route::triangulation() {
	initTriangles(2);
	addTriangle(new Triangle(corners[SW], corners[NW], corners[NE]));
	addTriangle(new Triangle(corners[SW], corners[SE], corners[NE]));
}
