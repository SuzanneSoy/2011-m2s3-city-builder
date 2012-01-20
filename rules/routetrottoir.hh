#ifndef _RULES_ROUTETROTTOIR_HH_
#define _RULES_ROUTETROTTOIR_HH_

#include "all_includes.hh"

class RouteTrottoirQuad : public Chose {
	private :
	Quad c;

	public :
	RouteTrottoirQuad(Quad _c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
