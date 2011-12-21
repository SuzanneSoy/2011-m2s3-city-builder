#ifndef _RULES_BATIMENTMAISONBLOCK_HH_
#define _RULES_BATIMENTMAISONBLOCK_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class BatimentQuadMaisonBlock : public Chose {
    private :
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
	int height;

    public :

	BatimentQuadMaisonBlock(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height);
	virtual ~BatimentQuadMaisonBlock();
	virtual bool split();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void getBoundingBoxPoints();
};

#endif
