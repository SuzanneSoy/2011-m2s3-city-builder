#ifndef _GEOMETRY_SEGMENT_HH_
#define _GEOMETRY_SEGMENT_HH_

#include "all_includes.hh"

class Segment {
    public :
	Vertex u;
	Vertex v;

    public :
	Segment(Vertex u, Vertex v);
	float length();
	float width();
	float height();
	Vertex center();
	Vertex at(float);
	Segment reduce(float value);
	Vertex randomPos(int seed, int n, float a, float b); // Renvoie un vertex sur le segment [u,v], à une position entre a et b.
};

#endif
