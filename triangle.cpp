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
		int ax = v1.x - v2.x;
		int ay = v1.y - v2.y;
		int az = v1.z - v2.z;
		int bx = v2.x - v3.x;
		int by = v2.y - v3.y;
		int bz = v2.z - v3.z;
		
		Vertexf normal;
		
		float x = (float)((ay * bz) - (az * by));
		float y = (float)((az * bx) - (ax * bz));
		float z = (float)((ax * by) - (ay * bx));
		float length = sqrt(x*x + y*y + z*z);
		
		normal.x = x/length;
		normal.y = y/length;
		normal.z = z/length;
		
		return normal;
}

void Triangle::display() {
	// glDisable(GL_LIGHTING);
	// glDisable(GL_TEXTURE_2D);
	// glBegin(GL_LINES);
	// glColor3ub(255,255,0);
	// Vertex v = (v1 + v2 + v3) / 3;
	// glVertex3d(v.x*10,v.y*10,v.z*10);
	// glVertex3d(v.x*10+normal.x*50,v.y*10+normal.y*50,v.z*10+normal.z*50);
	// glEnd( );
	// glEnable(GL_LIGHTING);
	
	View::setColor(r,g,b);
	glNormal3d(normal.x,normal.y,normal.z);
	glBegin(GL_TRIANGLES);
	glVertex3d(v1.x*10,v1.y*10,v1.z*10);
	glVertex3d(v2.x*10,v2.y*10,v2.z*10);
	glVertex3d(v3.x*10,v3.y*10,v3.z*10);
	glEnd();
}
