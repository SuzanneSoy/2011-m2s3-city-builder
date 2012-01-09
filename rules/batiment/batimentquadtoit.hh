#ifndef _RULES_BATIMENT_BATIMENTQUADTOIT_HH_
#define _RULES_BATIMENT_BATIMENTQUADTOIT_HH_

#include "all_includes.hh"

// TOTO en faire un classe abstraite et définir des classe filles pour les différents types de toits.
class BatimentQuadToit: public Chose {
    private :
	Quad c;
	float height;

    public :

	BatimentQuadToit(Quad c, float height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
