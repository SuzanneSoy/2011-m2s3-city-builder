#ifndef _RULES_QUAD_HERBE_HH_
#define _RULES_QUAD_HERBE_HH_

#include "all_includes.hh"


class TerrainQuadHerbe : public Chose {
    private :
	Vertex corner[4];
	int red; // DEBUG

    public :
	TerrainQuadHerbe(Vertex ne, Vertex se, Vertex sw, Vertex nw);
	TerrainQuadHerbe(int red, Vertex ne, Vertex se, Vertex sw, Vertex nw); // DEBUG
	virtual ~TerrainQuadHerbe();
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};


#endif
