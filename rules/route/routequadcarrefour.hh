#ifndef _CARREFOUR_ROUTE_HH_
#define _CARREFOUR_ROUTE_HH_

#include "all_includes.hh"

class RouteQuadCarrefour : public Chose {
    private :
	Vertex corner[4];

    public :
	RouteQuadCarrefour(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual ~RouteQuadCarrefour();
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
