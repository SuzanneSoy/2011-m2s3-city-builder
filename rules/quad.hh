#ifndef _RULES_QUAD_HH_
#define _RULES_QUAD_HH_

#include "all_includes.hh"

// Quad est un quadrilatère
class Quad : public Chose {
public:
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
public:
	Quad(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual bool subdivide();
	virtual void triangulation();
	void offset(/*Cardinal*/int side, int n);
	Vertex& corner(Coin corner, int rotation);
};


#endif
