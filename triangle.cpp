#include "all_includes.hh"

Triangle::Triangle(Vertex a, Vertex b, Vertex c): a(a), b(b), c(c) {
	// TODO : calcul de la normale.
}

std::ostream& operator<<(std::ostream& os, const Triangle* t) {
	return os << *t;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
	return os << "Triangle " << t.a << "--" << t.b << "--"  << t.c << "-- cycle";
}
