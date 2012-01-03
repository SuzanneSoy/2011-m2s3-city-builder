#ifndef _RULES_ROUTE_TRI_CHAUSSEE_HH_
#define _RULES_ROUTE_TRI_CHAUSSEE__HH_

#include "all_includes.hh"

class RouteTriChaussee : public Chose {
    private :
	Vertex corner[3];

    public :
	RouteTriChaussee(Vertex left, Vertex top, Vertex right);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
