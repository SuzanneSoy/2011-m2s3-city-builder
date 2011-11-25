#ifndef _RULES_ROUTE_HH_
#define _RULES_ROUTE_HH_

#include "all_includes.hh"

class Route : Chose {
public:
	Vertex corners[4];
public:
	Route(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void subdivide();
	virtual void triangulation();
public:
	friend std::ostream& operator<<(std::ostream& os, const Route& r);
	friend std::ostream& operator<<(std::ostream& os, const Route* r);
};

#endif
