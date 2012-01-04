#ifndef _CARREFOUR_ROUTE_HH_
#define _CARREFOUR_ROUTE_HH_

#include "all_includes.hh"

class RouteQuadCarrefour : public Chose {
    private :
	Quad c;

    public :
	RouteQuadCarrefour(Quad c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
