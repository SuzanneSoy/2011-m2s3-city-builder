#ifndef _CARREFOUR_ROUTE_HH_
#define _CARREFOUR_ROUTE_HH_

#include <iostream>
#include "../vertex.hh"
#include "../rules.hh"

class Carrefour {
public:
	Vertex corners[4];
public:
	Carrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw);
};

std::ostream& operator<<(std::ostream& os, const Carrefour& c);
std::ostream& operator<<(std::ostream& os, const Carrefour* c);

#endif
