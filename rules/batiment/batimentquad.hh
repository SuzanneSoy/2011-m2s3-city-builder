#ifndef _RULES_BATIMENT_HH_
#define _RULES_BATIMENT_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class BatimentQuad : public Chose {
public:
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
public:
	static const int minHeight = 400;
	static const int maxHeight = 800;
public:
	BatimentQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	int width();
	int height();
	virtual bool subdivide();
	virtual void triangulation();
};

#endif
