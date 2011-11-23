#ifndef _TRIANGLE_HH_
#define _TRIANGLE_HH_

#include "all_includes.hh"

class Triangle {
public:
	Vertex a;
	Vertex b;
	Vertex c;
public:
	Triangle(Vertex a, Vertex b, Vertex c);
public:
	friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
};

#endif
