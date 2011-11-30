#ifndef _RULES_BATIMENT_HH_
#define _RULES_BATIMENT_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class Batiment : public Chose {
public:
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
public:
	Batiment(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	int width();
	int height();
	virtual bool subdivide();
	virtual void triangulation();
};

#endif
