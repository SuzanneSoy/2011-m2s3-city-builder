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
	static Vertex fromSpherical(float r, float xAngle, float yAngle);

	public:
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v);
	friend Vertex operator+(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& v);
	friend Vertex operator*(const Vertex& v, const int n);
	friend Vertex operator/(const Vertex& v, const int n);
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
	static Vertexf fromSpherical(float r, float xAngle, float yAngle);

	public:
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v);
	friend Vertexf operator+(const Vertexf& u, const Vertexf& v);
	friend Vertexf operator-(const Vertexf& u, const Vertexf& v);
	friend Vertexf operator-(const Vertexf& v);
	friend Vertexf operator*(const Vertexf& v, const int n);
	friend Vertexf operator/(const Vertexf& v, const int n);
	friend Vertexf operator+(const Vertexf& u, const Vertex& v);
	friend Vertexf operator-(const Vertexf& u, const Vertex& v);
};

#endif
