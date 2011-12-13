#ifndef _SEGMENT_HH_
#define _SEGMENT_HH_

#include "all_includes.hh"

class Segment {
    private :
	Vertex u;
	Vertex v;

    public :
	Segment(Vertex u, Vertex v);
	int length();
	int width();
	int height();
	Vertex randomPos(int seed, int n, int a, int b); // Renvoir un vertex sur le segment [u,v], à une position entre a% and b%.
};

#endif
