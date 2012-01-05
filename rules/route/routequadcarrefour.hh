#ifndef _RULES_ROUTE_ROUTEQUADCARREFOUR_HH_
#define _RULES_ROUTE_ROUTEQUADCARREFOUR_HH_

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
