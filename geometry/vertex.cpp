#include "all_includes.hh"

Vertex::Vertex() {}

Vertex::Vertex(float _x, float _y, float _z): x(_x), y(_y), z(_z) {
	// TODO : DEBUG
	if (!(std::isfinite(x) && std::isfinite(y) && std::isfinite(z)))
		std::cout << "Attempted to create vertex with bad data !" << std::endl;
}

float Vertex::norm() const { return std::sqrt(x*x + y*y + z*z); }

Vertex Vertex::projectOn(Vertex v) const {
	// http://www.developpez.net/forums/d202580/applications/developpement-2d-3d-jeux/contribuez/faq-mat-quat-ajout-calculs-vectoriels/
	float scalaire = (this->x)*(v.x) + (this->y)*(v.y) + (this->z)*(v.z);
	float norme = v.norm();
	return Vertex(v.x, v.y, v.z) * scalaire / (norme * norme);
}

Vertex Vertex::setNorm(float n) const {
	return (*this * n / norm());
}

float Vertex::cosAngle(Vertex v) const {
	// http://www.developpez.net/forums/d202580/applications/developpement-2d-3d-jeux/contribuez/faq-mat-quat-ajout-calculs-vectoriels/
	return ((this->x*v.x + this->y*v.y + this->z*v.z) / (norm()*v.norm()));
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
