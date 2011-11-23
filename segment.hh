#ifndef _SEGMENT_HH_
#define _SEGMENT_HH_

#include "all_includes.hh"

class Segment {
public:
	Vertex u;
	Vertex v;
public:
	Segment(Vertex u, Vertex v);
	int length();
	int width();
	int height();
};

#endif
