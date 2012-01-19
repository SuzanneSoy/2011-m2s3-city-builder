#ifndef _RULES_ROUTETROTTOIR_HH_
#define _RULES_ROUTETROTTOIR_HH_

#include "all_includes.hh"

class TrottoirQuad : public Chose {
	private :
	Quad c;

	public :
	TrottoirQuad(Quad _c);
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
