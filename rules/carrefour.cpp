#include "carrefour.hh"

Carrefour::Carrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
	addEntropy(ne,se,sw,nw);
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
	return os << "Carrefour " << c.ne << "-" << c.se << "-" << c.sw << "-" << c.nw;
}

void Carrefour::triangulation() {
	triangles.reserve(2);
	addTriangle(new Triangle(sw, nw, ne, 0x80, 0x80, 0x80));
	addTriangle(new Triangle(sw, se, ne, 0x80, 0x80, 0x80));
}
