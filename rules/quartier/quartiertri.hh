#ifndef _RULES_TRIANGLE_HH_
#define _RULES_TRIANGLE_HH_

#include "all_includes.hh"


class QuartierTri : public Chose {
    public :
	Vertex c[3];

    public :
	QuartierTri(Vertex left, Vertex top, Vertex right);
	virtual ~QuartierTri();
	virtual bool split();
	virtual void triangulation();
	static Chose* factory(int seed, int n, Vertex left, Vertex top, Vertex right);
	virtual void getBoundingBoxPoints();
};

#endif
