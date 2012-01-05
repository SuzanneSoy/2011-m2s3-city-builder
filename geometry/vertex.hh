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
	float norm();
	Vertex projectOn(Vertex v);
	Vertex setNorm(float n);
	Vertex perpendicular(); // Perpendiculaire 2D dans le sens contraire des aiguilles d'une montre.
	float cosAngle(Vertex v); // cosinus de l'angle entre this et v.
	static Vertex fromSpherical(float r, float xAngle, float yAngle);
	friend Vertex intersection(Vertex a, Vertex b, Vertex c, Vertex d); // Intersection entre (a,b) et (c,d).

	public :
	operator Vertex();
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v);
	friend Vertex operator+(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& v);
	friend Vertex operator*(const Vertex& v, const float n);
	friend Vertex operator*(const Vertex& u, const Vertex& v);
	friend Vertex operator/(const Vertex& v, const int n);
	friend Vertex operator/(const Vertex& v, const float f);
};

/*
class Vertex {
	public :
	float x;
	float y;
	float z;

	public :
	Vertex();
	Vertex(float x, float y, float z);
	float norm();
	static Vertex fromSpherical(float r, float xAngle, float yAngle);

	public :
	operator Vertex();
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v);
	friend Vertex operator+(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& v);
	friend Vertex operator*(const Vertex& v, const int n);
	friend Vertex operator*(const Vertex& u, const Vertex& v);
	friend Vertex operator/(const Vertex& v, const int n);
	friend Vertex operator/(const Vertex& v, const float f);
	friend Vertex operator+(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& u, const Vertex& v);
};
*/
#endif
