#include "carrefour.hh"

Carrefour::Carrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	corners[NE]=ne;
	corners[SE]=se;
	corners[SW]=sw;
	corners[NW]=nw;
	triangulation();
}

bool Carrefour::subdivide() {
	// TODO
	return false;
}

std::ostream& operator<<(std::ostream& os, const Carrefour* c) {
	return os << *c;
}

std::ostream& operator<<(std::ostream& os, const Carrefour& c) {
	return os << "Carrefour " << c.corners[NE] << "-" << c.corners[SE] << "-" << c.corners[NW] << "-" << c.corners[SW];
}

void Carrefour::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(corners[SW], corners[NW], corners[NE], 0x80, 0x80, 0x80));
	addTriangle(new Triangle(corners[SW], corners[SE], corners[NE], 0x80, 0x80, 0x80));
}
