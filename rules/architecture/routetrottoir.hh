#ifndef _RULES_ARCHITECTURE_ROUTE_HH_
#define _RULES_ARCHITECTURE_ROUTE_HH_

#include "all_includes.hh"

class TrottoirQuad : public Chose {
	private :
	Quad c;
	float height;

	public :
	TrottoirQuad(Quad _c, float _height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

class RouteQuad : public Chose {
    private :
	Quad c;

    public :
	RouteQuad(Quad _c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
