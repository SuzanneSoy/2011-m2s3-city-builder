#include "all_includes.hh"

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3, unsigned char r, unsigned char g, unsigned char b): v1(v1), v2(v2), v3(v3), r(r), g(g), b(b) {
	// TODO : calcul de la normale.
	normal = normalVector(v1,v2,v3);
}

std::ostream& operator<<(std::ostream& os, const Triangle* t) {
	return os << *t;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
	return os << "Triangle " << t.v1 << "--" << t.v2 << "--"  << t.v3 << "-- cycle";
}

Vertexf Triangle::normalVector(Vertex v1, Vertex v2, Vertex v3) {
	Vertexf normal = (v1 - v2)*(v2 - v3);
	return normal / normal.norm();
}

void Triangle::display() {
	// glDisable(GL_LIGHTING);
	// glDisable(GL_TEXTURE_2D);
	// glBegin(GL_LINES);
	// glColor3ub(255,255,0);
	// Vertex v = (v1 + v2 + v3) / 3;
	// glVertex3d(v.x,v.y,v.z);
	// glVertex3d(v.x+normal.x*50,v.y+normal.y*50,v.z+normal.z*50);
	// glEnd( );
	// glEnable(GL_LIGHTING);
	
	View::setColor(r,g,b);
	glNormal3d(normal.x,normal.y,normal.z);
	// glBegin(GL_TRIANGLES);
	glVertex3d(v1.x,v1.y,v1.z);
	glVertex3d(v2.x,v2.y,v2.z);
	glVertex3d(v3.x,v3.y,v3.z);
	// glEnd();
}
