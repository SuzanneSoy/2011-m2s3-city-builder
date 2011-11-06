#include "segment.hh"
#include "vertex.hh"
#include <math.h>

Segment::Segment(Vertex u, Vertex v): u(u), v(v) {}

int Segment::length() {
	int x = u.x - v.x;
	int y = u.y - v.y;
	return sqrt(x*x + y*y);
}
