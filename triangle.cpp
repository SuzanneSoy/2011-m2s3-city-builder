#include "all_includes.hh"

Triangle::Triangle(Vertex a, Vertex b, Vertex c): a(a), b(b), c(c) {
	std::cout << this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
	return os << "Triangle " << t.a << "--" << t.b << "--"  << t.c << "-- cycle";
}
