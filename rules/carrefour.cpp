#include "carrefour.hh"

Carrefour::Carrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	corners[NE]=ne;
	corners[SE]=se;
	corners[SW]=sw;
	corners[NW]=nw;
	std::cout << this << std::endl;
}

void Carrefour::subdivide() {
	// TODO
}

std::ostream& operator<<(std::ostream& os, const Carrefour* c) {
	return os << *c;
}

std::ostream& operator<<(std::ostream& os, const Carrefour& c) {
	return os << "Carrefour " << c.corners[NE] << "-" << c.corners[SE] << "-" << c.corners[NW] << "-" << c.corners[SW];
}

void Carrefour::triangulation() {
	initTriangles(2);
	addTriangle(new Triangle(corners[SW], corners[NW], corners[NE]));
	addTriangle(new Triangle(corners[SW], corners[SE], corners[NE]));
}
