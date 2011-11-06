#ifndef _RULES_ROUTE_HH_
#define _RULES_ROUTE_HH_

#include <iostream>
#include "../vertex.hh"
#include "../rules.hh"

class Route {
public:
	Vertex corners[4];
public:
	Route(Vertex ne, Vertex se, Vertex sw, Vertex nw);
};

std::ostream& operator<<(std::ostream& os, const Route& r);
std::ostream& operator<<(std::ostream& os, const Route* r);

#endif
