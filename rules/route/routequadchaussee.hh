#ifndef _RULES_ROUTE_ROUTEQUADCHAUSSEE_HH_
#define _RULES_ROUTE_ROUTEQUADCHAUSSEE_HH_

#include "all_includes.hh"

class RouteQuadChaussee : public Chose {
    private :
	Quad c;

    public :
	RouteQuadChaussee(Quad c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
