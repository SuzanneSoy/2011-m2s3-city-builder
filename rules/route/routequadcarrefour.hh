#ifndef _CARREFOUR_ROUTE_HH_
#define _CARREFOUR_ROUTE_HH_

#include "all_includes.hh"

class RouteQuadCarrefour : public Chose {
    private :
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;

    public :
	RouteQuadCarrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual bool subdivide();
	virtual void triangulation();
	virtual std::vector<Vertex*> getBoundingBoxPoints() const;
};

#endif
