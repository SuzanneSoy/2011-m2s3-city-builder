#ifndef _RULES_ROUTE_HH_
#define _RULES_ROUTE_HH_

#include "all_includes.hh"

class RouteQuadChaussee : public Chose {
    private :
	Vertex corner[4];

    public :
	RouteQuadChaussee(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual ~RouteQuadChaussee();
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
