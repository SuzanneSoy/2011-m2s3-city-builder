#ifndef _TRIANGLE_HH_
#define _TRIANGLE_HH_

#include "all_includes.hh"

class Triangle {
	public:
	Vertex v1;
	Vertex v2;
	Vertex v3;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Vertexf normal;

	public:
	friend std::ostream& operator<<(std::ostream& os, const Triangle* t);
	friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
	Triangle(Vertex v1, Vertex v2, Vertex v3, unsigned char r, unsigned char g, unsigned char b);
	void display();
	
	private :
	Vertexf normalVector(Vertex v1, Vertex v2, Vertex v3);
};

#endif
