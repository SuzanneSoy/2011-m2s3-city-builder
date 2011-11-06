#ifndef _VERTEX_HH_
#define _VERTEX_HH_

#include <iostream>

class Vertex {
public:
	int x;
	int y;
	//int z;
public:
	Vertex();
	Vertex(int x, int y);
	Vertex add(int dx, int dy);
};

std::ostream& operator<<(std::ostream& os, const Vertex& v);

#endif
