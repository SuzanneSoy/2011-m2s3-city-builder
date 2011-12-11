#ifndef _CARREFOUR_ROUTE_HH_
#define _CARREFOUR_ROUTE_HH_

#include "all_includes.hh"

class Carrefour : public Chose {
public:
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
public:
	Carrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual bool subdivide();
	virtual void triangulation();
	// TODO : Carrefour::replacePoint (pour pouvoir transformer un carrefour 4 en carrefour 5 et +).
public:
	friend std::ostream& operator<<(std::ostream& os, const Carrefour& c);
	friend std::ostream& operator<<(std::ostream& os, const Carrefour* c);
};

#endif
