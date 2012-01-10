#ifndef _RULES_TERRAIN_TERRAINQUADHERBE_HH_
#define _RULES_TERRAIN_TERRAINQUADHERBE_HH_

#include "all_includes.hh"


class TerrainQuadHerbe : public Chose {
    private :
	Quad c;

    public :
	TerrainQuadHerbe(Quad _c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};


#endif
