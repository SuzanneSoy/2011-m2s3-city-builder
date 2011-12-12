#ifndef _RULES_TRIANGLE_HH_
#define _RULES_TRIANGLE_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class QuartierTri : public Chose {
public:
	Vertex corner[3];
public:
	QuartierTri(Vertex left, Vertex top, Vertex right);
	virtual bool subdivide();
	virtual void triangulation();
	static Chose* factory(int seed, int n, Vertex left, Vertex top, Vertex right);
};

#endif
