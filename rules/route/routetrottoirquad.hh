#ifndef _RULES_ROUTE_ROUTETROTTOIRQUAD_HH_
#define _RULES_ROUTE_ROUTETROTTOIRQUAD_HH_

#include "all_includes.hh"


class RouteTrottoirQuad : public Chose {
private :
	Quad c;
public :
	static const int minHeight = 400;
	static const int maxHeight = 800;
public :
	RouteTrottoirQuad(Quad _c);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
	static Chose* factory(int seed, int n, Quad c); // TODO : est-ce une factory ou non, où la met-on…
};

#endif
