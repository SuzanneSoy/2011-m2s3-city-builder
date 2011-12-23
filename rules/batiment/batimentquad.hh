#ifndef _RULES_BATIMENT_HH_
#define _RULES_BATIMENT_HH_

#include "all_includes.hh"


class BatimentQuad : public Chose {
    private :
	Vertex c[4];
	Cardinal entry;

    public :
	static const int minHeight = 400;
	static const int maxHeight = 800;

	BatimentQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw, Cardinal door);
	virtual ~BatimentQuad();
	virtual bool split();
	virtual void triangulation();
	Chose* factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw);
	virtual void getBoundingBoxPoints();
};

#endif
