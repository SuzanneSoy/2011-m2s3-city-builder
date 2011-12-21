#ifndef _RULES_QUADRILATERE_HH_
#define _RULES_QUADRILATERE_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class QuartierQuad : public Chose {
public:
	Vertex corner[4];
public:
	QuartierQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual ~QuartierQuad();
	virtual bool split();
	virtual void triangulation();
	static Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void getBoundingBoxPoints();
};

#endif
