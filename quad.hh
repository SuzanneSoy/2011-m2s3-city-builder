#ifndef _QUAD_HH_
#define _QUAD_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class Quad {
public:
	Vertex corner[4];
public:
	Quad();
	Quad(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	void offset(/*Cardinal*/int side, int offset);
	int minLength();
	int maxLength();
};


#endif
