#ifndef _VERTEX_HH_
#define _VERTEX_HH_

#include <iostream>

class Vertex {
public:
	int x;
	int y;
	int z;
public:
	Vertex();
	Vertex(int x, int y, int z);
public:
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v);
	friend Vertex operator+(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& u, const Vertex& v);
	friend Vertex operator-(const Vertex& v);
	friend Vertex operator*(const Vertex& v, const int n);
	friend Vertex operator/(const Vertex& v, const int n);
};

#endif
