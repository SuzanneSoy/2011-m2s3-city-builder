#ifndef _RULES_BATIMENTJARDIN_HH
#define _RULES_BATIMENTJARDIN_HH

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class BatimentQuadJardin : public Chose {
public:
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
public:
	static const int minHeight = 400;
	static const int maxHeight = 800;
public:
	BatimentQuadJardin(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	int width();
	int height();
	virtual bool subdivide();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
};

#endif
