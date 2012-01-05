#ifndef _RULES_BATIMENT_BATIMENTQUADFENETRE_HH_
#define _RULES_BATIMENT_BATIMENTQUADFENETRE_HH_

#include "all_includes.hh"

class BatimentQuadFenetre: public Chose {
    private :
	Quad c;
	int height;

    public :

	BatimentQuadFenetre(Quad c, int height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
