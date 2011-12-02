#include "all_includes.hh"

Vertex::Vertex() {}

Vertex::Vertex(int x, int y, int z): x(x), y(y), z(z) {}

float Vertex::norm() { return std::sqrt(x*x + y*y + z*z); }

// TODO : this is 2D only, use Vertex2d.
Vertex intersection(Vertex a, Vertex b, Vertex c, Vertex d) {
	// Note : si les deux lignes sont parallèles, on risque fort
	// d'avoir une division par zéro.
	// http://en.wikipedia.org/wiki/Line-line_intersection
	long long x1 = a.x; long long y1 = a.y;
	long long x2 = b.x; long long y2 = b.y;
	long long x3 = c.x; long long y3 = c.y;
	long long x4 = d.x; long long y4 = d.y;
	long long denominator =  ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4));
	return Vertex(
		((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4)) / denominator,
		((x1*y2-y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)) / denominator,
		0
	);
}

Vertex::operator Vertexf() { return Vertexf(x,y,z); }

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
	return os << "(" << v.x << "," << v.y << "," << v.z << ")";
}

Vertex operator+(const Vertex& u, const Vertex& v) {
	return Vertex(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vertex operator-(const Vertex& u, const Vertex& v) {
	return Vertex(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vertex operator+(const Vertex& u, const Vertexf& v) {
	return Vertex(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vertex operator-(const Vertex& u, const Vertexf& v) {
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




Vertexf::Vertexf() {}

Vertexf::Vertexf(float x, float y, float z): x(x), y(y), z(z) {}

float Vertexf::norm() { return std::sqrt(x*x + y*y + z*z); }

Vertexf::operator Vertex() { return Vertex(x,y,z); }

std::ostream& operator<<(std::ostream& os, const Vertexf& v) {
	return os << "(" << v.x << "," << v.y << "," << v.z << ")";
}

Vertexf operator+(const Vertexf& u, const Vertexf& v) {
	return Vertexf(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vertexf operator-(const Vertexf& u, const Vertex& v) {
	return Vertexf(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vertexf operator+(const Vertexf& u, const Vertex& v) {
	return Vertexf(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vertexf operator-(const Vertexf& u, const Vertexf& v) {
	return Vertexf(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vertexf operator-(const Vertexf& v) {
	return Vertexf(-v.x, -v.y, -v.z);
}

Vertexf operator*(const Vertexf& v, const int n) {
	return Vertexf(v.x * n, v.y * n, v.z * n);
}

Vertexf operator*(const Vertexf& u, const Vertexf& v) {
	return Vertexf(
		(u.y * v.z) - (u.z * v.y),
		(u.z * v.x) - (u.x * v.z),
		(u.x * v.y) - (u.y * v.x)
	);
}

Vertexf operator/(const Vertexf& v, const int n) {
	return Vertexf(v.x / n, v.y / n, v.z / n);
}

Vertexf operator/(const Vertexf& v, const float f) {
	return Vertexf(v.x / f, v.y / f, v.z / f);
}

Vertexf Vertexf::fromSpherical(float r, float xAngle, float yAngle) {
	// http://electron9.phys.utk.edu/vectors/3dcoordinates.htm
	return Vertexf(
		r * std::sin(xAngle / 180 * 3.14159) * std::cos(yAngle / 180 * 3.14159),
		r * std::sin(xAngle / 180 * 3.14159) * std::sin(yAngle / 180 * 3.14159),
		r * std::cos(xAngle / 180 * 3.14159)
	);
}
