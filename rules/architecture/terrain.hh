#ifndef _RULES_ARCHITECTURE_TERRAIN_HH_
#define _RULES_ARCHITECTURE_TERRAIN_HH_

#include "all_includes.hh"

class TerrainTri : public Chose {
    private :
	Triangle c;

    public :
	TerrainTri(Triangle _c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

class TerrainQuad : public Chose {
    private :
	Quad c;

    public :
	TerrainQuad(Quad _c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
