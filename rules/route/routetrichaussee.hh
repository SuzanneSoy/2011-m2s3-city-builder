#ifndef _RULES_ROUTE_ROUTETRICHAUSSEE_HH_
#define _RULES_ROUTE_ROUTETRICHAUSSEE_HH_

#include "all_includes.hh"

class RouteTriChaussee : public Chose {
    private :
	Triangle c;

    public :
	RouteTriChaussee(Triangle c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
