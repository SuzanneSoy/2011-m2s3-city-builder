#ifndef _RULES_BATIMENTMAISON_HH_
#define _RULES_BATIMENTMAISON_HH_

#include "all_includes.hh"


class BatimentQuadMaison : public Chose {
    private :
	Vertex corner[4];

    public :
	static const int minHeight = 400;
	static const int maxHeight = 800;

	BatimentQuadMaison(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual ~BatimentQuadMaison();
	virtual bool split();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void getBoundingBoxPoints();
};

#endif
