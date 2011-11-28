#ifndef _TRIANGLE_HH_
#define _TRIANGLE_HH_

#include "all_includes.hh"

class Triangle {
public:
	Vertex a;
	Vertex b;
	Vertex c;
	Vertex normal;
public:
	Triangle(Vertex a, Vertex b, Vertex c);
	void display();
public:
	friend std::ostream& operator<<(std::ostream& os, const Triangle* t);
	friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
};

#endif
