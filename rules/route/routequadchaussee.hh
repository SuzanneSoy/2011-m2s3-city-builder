#ifndef _RULES_ROUTE_QUAD_CHAUSSEE_HH_
#define _RULES_ROUTE_QUAD_CHAUSSEE_HH_

#include "all_includes.hh"

class RouteQuadChaussee : public Chose {
    private :
	Vertex c[4];

    public :
	RouteQuadChaussee(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual ~RouteQuadChaussee();
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
