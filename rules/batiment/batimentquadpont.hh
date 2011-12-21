#ifndef _RULES_BATIMENTPONT_HH_
#define _RULES_BATIMENTPONT_HH_

#include "all_includes.hh"

// RectangleRoutes est un quadrilatère de routes avec des angles aux coins égaux à 90°.
class BatimentQuadPont: public Chose {
    private :
	Vertex ne;
	Vertex se;
	Vertex sw;
	Vertex nw;
	int height;

    public :

	BatimentQuadPont();
	BatimentQuadPont(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height);
	virtual ~BatimentQuadPont();
	virtual bool split();
	virtual bool merge();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void getBoundingBoxPoints();
};

#endif
