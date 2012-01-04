#ifndef _RULES_BATIMENTTOIT_HH_
#define _RULES_BATIMENTTOIT_HH_

#include "all_includes.hh"

// TOTO en faire un classe abstraite et définir des classe filles pour les différents types de toits.
class BatimentQuadToit: public Chose {
    private :
	Quad c;
	int height;

    public :

	BatimentQuadToit(Quad c, int height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
