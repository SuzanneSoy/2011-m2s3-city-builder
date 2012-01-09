#ifndef _RULES_BATIMENT_BATIMENTQUADFENETRE_HH_
#define _RULES_BATIMENT_BATIMENTQUADFENETRE_HH_

#include "all_includes.hh"

class BatimentQuadFenetre: public Chose {
    private :
	Quad c;
	float height;

    public :

	BatimentQuadFenetre(Quad c, float height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
