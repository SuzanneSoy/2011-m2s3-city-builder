#ifndef _RULES_BATIMENT_BATIMENTQUADPONT_HH_
#define _RULES_BATIMENT_BATIMENTQUADPONT_HH_

#include "all_includes.hh"


class BatimentQuadPont: public Chose {
    private :
	Quad c;
	float height;

    public :
	BatimentQuadPont(Quad c, float height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
