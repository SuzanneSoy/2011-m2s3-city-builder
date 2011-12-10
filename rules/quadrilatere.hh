#ifndef _RULES_QUADRILATERE_HH_
#define _RULES_QUADRILATERE_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class Quadrilatere : public Chose {
public:
	Vertex corner[4];
public:
	Quadrilatere(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual bool subdivide();
	virtual void triangulation();
	static Chose* factory(Vertex ne, Vertex se, Vertex sw, Vertex nw);
};

#endif
