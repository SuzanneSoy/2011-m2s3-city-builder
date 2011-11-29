#include "all_includes.hh"

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3, unsigned char r, unsigned char g, unsigned char b): v1(v1), v2(v2), v3(v3), r(r), g(g), b(b) {
	// TODO : calcul de la normale.
	normal = Vertex(0,0,1);
}

std::ostream& operator<<(std::ostream& os, const Triangle* t) {
	return os << *t;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
	return os << "Triangle " << t.v1 << "--" << t.v2 << "--"  << t.v3 << "-- cycle";
}

void Triangle::display() {
	glColor3ub(r, g, b);
	//std::cout << (int)r << "," << (int)g << "," << (int)b << std::endl;
	glNormal3d(normal.x,normal.y,normal.z);
	glBegin(GL_TRIANGLES);
	glVertex3d(v1.x,v1.y,v1.z);
	glVertex3d(v2.x,v2.y,v2.z);
	glVertex3d(v3.x,v3.y,v3.z);
	glEnd();
}
