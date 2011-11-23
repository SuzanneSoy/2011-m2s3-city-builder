#ifndef _RULES_BATIMENT_HH_
#define _RULES_BATIMENT_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class Batiment : public Chose {
public:
	Vertex ne;
	Vertex sw;
	int seed;
public:
	Batiment(Vertex ne, Vertex sw);
	int width();
	int height();
	virtual void subdivide();
	virtual void triangulation();
};

std::ostream& operator<<(std::ostream& os, const Batiment& r);
std::ostream& operator<<(std::ostream& os, const Batiment* r);

#endif
