#include "all_includes.hh"

Vertex::Vertex() {}

Vertex::Vertex(int x, int y, int z): x(x), y(y), z(z) {}

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

Vertex operator/(const Vertex& v, const int n) {
	return Vertex(v.x / n, v.y / n, v.z / n);
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

Vertexf operator/(const Vertexf& v, const int n) {
	return Vertexf(v.x / n, v.y / n, v.z / n);
}

Vertexf Vertexf::fromSpherical(float r, float xAngle, float yAngle) {
	// http://electron9.phys.utk.edu/vectors/3dcoordinates.htm
	return Vertexf(
		r * std::sin(xAngle / 180 * 3.14159) * std::cos(yAngle / 180 * 3.14159),
		r * std::sin(xAngle / 180 * 3.14159) * std::sin(yAngle / 180 * 3.14159),
		r * std::cos(xAngle / 180 * 3.14159)
	);
}
