#ifndef _RULES_BATIMENTMAISONPONT_HH_
#define _RULES_BATIMENTMAISONPONT_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class BatimentQuadMaisonPont: public Chose {
    private :
	Vertex c[4];
	int height;

    public :

	BatimentQuadMaisonPont(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height);
	virtual ~BatimentQuadMaisonPont();
	virtual bool split();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void getBoundingBoxPoints();
};

#endif