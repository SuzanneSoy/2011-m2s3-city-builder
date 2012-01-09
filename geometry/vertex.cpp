#include "all_includes.hh"

Vertex::Vertex() {}

Vertex::Vertex(float x, float y, float z): x(x), y(y), z(z) {}

float Vertex::norm() const { return std::sqrt(x*x + y*y + z*z); }

// TODO : Ce code ne marche qu'en 2D !
Vertex intersection(Vertex a, Vertex b, Vertex c, Vertex d) {
	// Note : si les deux lignes sont parallèles, on risque fort
	// d'avoir une division par zéro.
	// http://en.wikipedia.org/wiki/Line-line_intersection
	float denominator =  ((a.x-b.x)*(c.y-d.y) - (a.y-b.y)*(c.x-d.x));
	return Vertex(
		((a.x*b.y-a.y*b.x)*(c.x-d.x) - (a.x-b.x)*(c.x*d.y-c.y*d.x)) / denominator,
		((a.x*b.y-a.y*b.x)*(c.y-d.y) - (a.y-b.y)*(c.x*d.y-c.y*d.x)) / denominator,
		0
	);
}

Vertex Vertex::projectOn(Vertex v) const {
	// http://www.developpez.net/forums/d202580/applications/developpement-2d-3d-jeux/contribuez/faq-mat-quat-ajout-calculs-vectoriels/
	float scalaire = (this->x)*(v.x) + (this->y)*(v.y);
	float normecarre = v.norm();
	normecarre *= normecarre;
	return Vertex(v.x * scalaire / normecarre, v.y * scalaire / normecarre, 0);
}

Vertex Vertex::setNorm(float n) const {
	return (*this * n / norm());
}

Vertex Vertex::perpendicularCw() const {
	return Vertex(-y, x, 0);
}

float Vertex::cosAngle(Vertex v) const {
	// http://www.developpez.net/forums/d202580/applications/developpement-2d-3d-jeux/contribuez/faq-mat-quat-ajout-calculs-vectoriels/
	//std::cout << "cosAngle " << *this << " " << v << " " << ((this->x*v.x + this->y*v.y) / (norm()*v.norm())) << " " << (norm()*v.norm()) << std::endl;
	return ((this->x*v.x + this->y*v.y) / (norm()*v.norm()));
}

float Vertex::angle(Vertex v) const {
	return std::acos(cosAngle(v));
}

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
	return os << "(" << v.x << "," << v.y << "," << v.z << ")";
}


Vertex operator+(const Vertex& u, const Vertex& v) {
	return Vertex(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vertex operator-(const Vertex& u, const Vertex& v) {
	return Vertex(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vertex operator-(const Vertex& v) {
	return Vertex(-v.x, -v.y, -v.z);
}

Vertex operator*(const Vertex& v, const float n) {
	return Vertex(v.x * n, v.y * n, v.z * n);
}

Vertex operator*(const Vertex& u, const Vertex& v) {
	return Vertex(
		(u.y * v.z) - (u.z * v.y),
		(u.z * v.x) - (u.x * v.z),
		(u.x * v.y) - (u.y * v.x)
	);
}

Vertex operator/(const Vertex& v, const float f) {
	return Vertex(v.x / f, v.y / f, v.z / f);
}

Vertex Vertex::fromSpherical(float r, float xAngle, float yAngle) {
	// http://electron9.phys.utk.edu/vectors/3dcoordinates.htm
	return Vertex(
		r * std::sin(xAngle / 180.f * Angle::Pi) * std::cos(yAngle / 180.f * Angle::Pi),
		r * std::sin(xAngle / 180.f * Angle::Pi) * std::sin(yAngle / 180.f * Angle::Pi),
		r * std::cos(xAngle / 180.f * Angle::Pi)
	);
}




/*

Vertex::Vertex() {}

Vertex::Vertex(float x, float y, float z): x(x), y(y), z(z) {}

float Vertex::norm() { return std::sqrt(x*x + y*y + z*z); }

Vertex::operator Vertex() { return Vertex(x,y,z); }

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
	return os << "(" << v.x << "," << v.y << "," << v.z << ")";
}

Vertex operator+(const Vertex& u, const Vertex& v) {
	return Vertex(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vertex operator-(const Vertex& u, const Vertex& v) {
	return Vertex(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vertex operator+(const Vertex& u, const Vertex& v) {
	return Vertex(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vertex operator-(const Vertex& u, const Vertex& v) {
	return Vertex(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vertex operator-(const Vertex& v) {
	return Vertex(-v.x, -v.y, -v.z);
}

Vertex operator*(const Vertex& v, const int n) {
	return Vertex(v.x * n, v.y * n, v.z * n);
}

Vertex operator*(const Vertex& u, const Vertex& v) {
	return Vertex(
		(u.y * v.z) - (u.z * v.y),
		(u.z * v.x) - (u.x * v.z),
		(u.x * v.y) - (u.y * v.x)
	);
}

Vertex operator/(const Vertex& v, const int n) {
	return Vertex(v.x / n, v.y / n, v.z / n);
}

Vertex operator/(const Vertex& v, const float f) {
	return Vertex(v.x / f, v.y / f, v.z / f);
}

Vertex Vertex::fromSpherical(float r, float xAngle, float yAngle) {
	// http://electron9.phys.utk.edu/vectors/3dcoordinates.htm
	return Vertex(
		r * std::sin(xAngle / 180 * 3.14159) * std::cos(yAngle / 180 * 3.14159),
		r * std::sin(xAngle / 180 * 3.14159) * std::sin(yAngle / 180 * 3.14159),
		r * std::cos(xAngle / 180 * 3.14159)
	);
}
*/
