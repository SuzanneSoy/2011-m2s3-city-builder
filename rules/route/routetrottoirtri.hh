#ifndef _RULES_ROUTE_ROUTETROTTOIRTRI_HH_
#define _RULES_ROUTE_ROUTETROTTOIRTRI_HH_

#include "all_includes.hh"


class RouteTrottoirTri : public Chose {
private :
	Triangle c;
public :
	static const int minHeight = 400;
	static const int maxHeight = 800;
public :
	RouteTrottoirTri(Triangle _c);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
	static Chose* factory(int seed, int n, Triangle c); // TODO : est-ce une factory ou non, où la met-on…
};

#endif
