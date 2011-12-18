#ifndef _RULES_ROUTE_HH_
#define _RULES_ROUTE_HH_

#include "all_includes.hh"

class RouteQuadChaussee : public Chose {
    private :
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;

    public :
	RouteQuadChaussee(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual ~RouteQuadChaussee();
	virtual bool split();
	virtual bool merge();
	virtual void triangulation();
	virtual std::vector<Vertex*> getBoundingBoxPoints() const;
};

#endif
