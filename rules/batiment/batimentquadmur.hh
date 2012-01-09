#ifndef _RULES_BATIMENT_BATIMENTQUADMUR_HH_
#define _RULES_BATIMENT_BATIMENTQUADMUR_HH_

#include "all_includes.hh"

class BatimentQuadMur: public Chose {
    private :
	Quad c;
	float height;

    public :

	BatimentQuadMur(Quad c, float height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
