#include "all_includes.hh"

// Triangle "rapide", sert juste aux calculs de coordonnées. Devrait
// être une superclasse de "triangle". Pour calculer le cosinus
// d'angles, on crée un objet triangle assez gros. C'est du
// gaspillage.
Triangle::Triangle() {
}
Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3): v1(v1), v2(v2), v3(v3) {
}

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3, unsigned char r, unsigned char g, unsigned char b)
	: v1(v1), v2(v2), v3(v3), r(r), g(g), b(b), vnormal(normal(v1,v2,v3)) {
}

std::ostream& operator<<(std::ostream& os, const Triangle* t) {
	return os << *t;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
	return os << "Triangle " << t.v1 << "--" << t.v2 << "--"  << t.v3 << "-- cycle";
}

Vertex Triangle::normal(Vertex v1, Vertex v2, Vertex v3) {
	Vertex normal = (v1 - v2)*(v2 - v3);
	return normal / normal.norm();
}

float Triangle::cosAngle() {
	return (v1-v2).cosAngle(v3-v2);
}

float Triangle::angle() {
	return std::acos(cosAngle());
}

float Triangle::minAngle() {
	float a2 = angle();
	float a3 = Triangle(v2,v3,v1).angle();
	float a1 = Angle::Pi - a2 - a3;
	return std::min(std::min(a1, a2), a3);
}

void Triangle::offsetBase(int offset) {
	Quad q = Quad(v2, v1, v3, v2);
	q.offset(S, -offset);
	v1 = q.corner[1];
	v2 = q.corner[0];
	v3 = q.corner[2];
}

void Triangle::display() {
	// glDisable(GL_LIGHTING);
	// glDisable(GL_TEXTURE_2D);
	// glBegin(GL_LINES);
	// glColor3ub(255,255,0);
	// Vertex v = (v1 + v2 + v3) / 3;
	// glVertex3d(v.x,v.y,v.z);
	// glVertex3d(v.x+vnormal.x*50,v.y+vnormal.y*50,v.z+vnormal.z*50);
	// glEnd( );
	// glEnable(GL_LIGHTING);

	View::setColor(r,g,b);
	glNormal3d(vnormal.x,vnormal.y,vnormal.z);
	// glBegin(GL_TRIANGLES);
	glVertex3d(v1.x,v1.y,v1.z);
	glVertex3d(v2.x,v2.y,v2.z);
	glVertex3d(v3.x,v3.y,v3.z);
	// glEnd();
}
