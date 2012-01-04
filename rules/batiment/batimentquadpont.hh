#ifndef _RULES_BATIMENTPONT_HH_
#define _RULES_BATIMENTPONT_HH_

#include "all_includes.hh"


class BatimentQuadPont: public Chose {
    private :
	Quad c;
	int height;

    public :
	BatimentQuadPont(Quad c, int height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
