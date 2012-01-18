#ifndef _GEOMETRY_VERTEX_HH_
#define _GEOMETRY_VERTEX_HH_

#include "all_includes.hh"

class Vertex {
	public :
	float x;
	float y;
	float z;

	public :
	Vertex();
	Vertex(float x, float y, float z);
	float norm() const;
	Vertex projectOn(Vertex v) const;
	Vertex setNorm(float n) const;
	float cosAngle(Vertex v) const; // cosinus de l'angle entre this et v.
	float angle(Vertex v) const; // Angle entre this et v.
	static Vertex fromSpherical(float r, float xAngle, float yAngle);

	public :
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v);
	friend Vertex operator+(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& v);
	friend Vertex operator*(const Vertex& v, const float n);
	friend Vertex operator*(const Vertex& u, const Vertex& v);
	friend Vertex operator/(const Vertex& v, const float f);
};

#endif
