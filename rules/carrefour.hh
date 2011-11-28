#ifndef _CARREFOUR_ROUTE_HH_
#define _CARREFOUR_ROUTE_HH_

#include "all_includes.hh"

class Carrefour : public Chose {
public:
	Vertex corners[4];
public:
	Carrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void subdivide();
	virtual void triangulation();
public:
	friend std::ostream& operator<<(std::ostream& os, const Carrefour& c);
	friend std::ostream& operator<<(std::ostream& os, const Carrefour* c);
};

#endif
