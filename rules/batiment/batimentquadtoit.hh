#ifndef _RULES_BATIMENTTOIT_HH_
#define _RULES_BATIMENTTOIT_HH_

#include "all_includes.hh"

// TOTO en faire un classe abstraite et définir des classe filles pour les différents types de toits.
class BatimentQuadToit: public Chose {
    private :
	Vertex c[4];
	int height;

    public :

	BatimentQuadToit(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height);
	virtual ~BatimentQuadToit();
	virtual bool split();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void getBoundingBoxPoints();
};

#endif
