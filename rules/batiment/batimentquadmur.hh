#ifndef _RULES_BATIMENT_BATIMENTQUADMUR_HH_
#define _RULES_BATIMENT_BATIMENTQUADMUR_HH_

#include "all_includes.hh"

class BatimentQuadMur: public Chose {
    private :
	Quad c;
	int height;

    public :

	BatimentQuadMur(Quad c, int height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
