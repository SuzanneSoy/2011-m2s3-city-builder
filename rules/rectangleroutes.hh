#ifndef _RULES_RECTANGLEROUTES_HH_
#define _RULES_RECTANGLEROUTES_HH_

#include <iostream>
#include "../vertex.hh"
#include "../directions.hh"
#include "../io.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class RectangleRoutes {
public:
	Vertex ne;
	Vertex sw;
	IO io [4];
	int seed;
public:
	RectangleRoutes(Vertex ne, Vertex sw, int seed);
	int width();
	int height();
	void subdivide();
};

std::ostream& operator<<(std::ostream& os, const RectangleRoutes& r);
std::ostream& operator<<(std::ostream& os, const RectangleRoutes* r);

#endif
