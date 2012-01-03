#ifndef _SEGMENT_HH_
#define _SEGMENT_HH_

#include "all_includes.hh"

class Segment {
    public :
	Vertex u;
	Vertex v;

    public :
	Segment(Vertex u, Vertex v);
	float length();
	int width();
	int height();
	Segment reduce(float value);
	Vertex randomPos(int seed, int n, int a, int b); // Renvoir un vertex sur le segment [u,v], à une position entre a% and b%.
};

#endif
