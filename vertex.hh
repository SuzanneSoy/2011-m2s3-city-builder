#ifndef _VERTEX_HH_
#define _VERTEX_HH_

#include "all_includes.hh"
class Vertexf;

class Vertex {
	public:
	int x;
	int y;
	int z;

	public:
	Vertex();
	Vertex(int x, int y, int z);
	float norm();
	static Vertex fromSpherical(float r, float xAngle, float yAngle);
	friend Vertex intersection(Vertex a, Vertex b, Vertex c, Vertex d); // Intersection entre (a,b) et (c,d).

	public:
	operator Vertexf();
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v);
	friend Vertex operator+(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& v);
	friend Vertex operator*(const Vertex& v, const int n);
	friend Vertex operator*(const Vertex& u, const Vertex& v);
	friend Vertex operator/(const Vertex& v, const int n);
	friend Vertex operator/(const Vertex& v, const float f);
	friend Vertex operator+(const Vertex& u, const Vertexf& v);
	friend Vertex operator-(const Vertex& u, const Vertexf& v);
};

class Vertexf {
	public:
	float x;
	float y;
	float z;

	public:
	Vertexf();
	Vertexf(float x, float y, float z);
	float norm();
	static Vertexf fromSpherical(float r, float xAngle, float yAngle);

	public:
	operator Vertex();
	friend std::ostream& operator<<(std::ostream& os, const Vertexf& v);
	friend Vertexf operator+(const Vertexf& u, const Vertexf& v);
	friend Vertexf operator-(const Vertexf& u, const Vertexf& v);
	friend Vertexf operator-(const Vertexf& v);
	friend Vertexf operator*(const Vertexf& v, const int n);
	friend Vertexf operator*(const Vertexf& u, const Vertexf& v);
	friend Vertexf operator/(const Vertexf& v, const int n);
	friend Vertexf operator/(const Vertexf& v, const float f);
	friend Vertexf operator+(const Vertexf& u, const Vertex& v);
	friend Vertexf operator-(const Vertexf& u, const Vertex& v);
};

#endif
