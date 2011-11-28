#include "route.hh"
#include "../vertex.hh"
#include "../directions.hh"

Route::Route(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	corners[NE]=ne;
	corners[SE]=se;
	corners[SW]=sw;
	corners[NW]=nw;
	triangulation();
}

bool Route::subdivide() {
	// TODO
	return false;
}

std::ostream& operator<<(std::ostream& os, const Route* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Route& r) {
	return os << "Route " << r.corners[NE] << "-" << r.corners[SE] << "-" << r.corners[NW] << "-" << r.corners[SW];
}

void Route::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(corners[SW], corners[NW], corners[NE]));
	addTriangle(new Triangle(corners[SW], corners[SE], corners[NE]));
}
