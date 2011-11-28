#include "all_includes.hh"

Triangle::Triangle(Vertex a, Vertex b, Vertex c): a(a), b(b), c(c) {
	// TODO : calcul de la normale.
	normal = Vertex(0,0,1);
}

std::ostream& operator<<(std::ostream& os, const Triangle* t) {
	return os << *t;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
	return os << "Triangle " << t.a << "--" << t.b << "--"  << t.c << "-- cycle";
}

void Triangle::display() {
	glNormal3d(normal.x,normal.y,normal.z);
	glVertex3d(a.x,a.y,a.z);
	glVertex3d(b.x,b.y,b.z);
	glVertex3d(c.x,c.y,c.z);
}
