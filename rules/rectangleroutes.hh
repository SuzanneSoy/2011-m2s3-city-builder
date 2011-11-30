#ifndef _RULES_RECTANGLEROUTES_HH_
#define _RULES_RECTANGLEROUTES_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°, et des côtés de longueur >= 10.
class RectangleRoutes : public Chose {
public:
	Vertex ne;
	Vertex sw;
public:
	RectangleRoutes(Vertex ne, Vertex sw);
	int width();
	int height();
	virtual bool subdivide();
	virtual void triangulation();
private:
	Chose* sub(Vertex ne, Vertex sw);
public:
	friend std::ostream& operator<<(std::ostream& os, const RectangleRoutes& r);
	friend std::ostream& operator<<(std::ostream& os, const RectangleRoutes* r);
};


#endif
