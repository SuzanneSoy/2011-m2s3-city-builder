#include "route.hh"
#include "../vertex.hh"
#include "../directions.hh"

Route::Route(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
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
	return os << "Route " << r.ne << "-" << r.se << "-" << r.sw << "-" << r.nw;
}

void Route::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(sw, nw, ne, 0x6c, 0x6c, 0x6c));
	addTriangle(new Triangle(sw, se, ne, 0x6c, 0x6c, 0x6c));
}
