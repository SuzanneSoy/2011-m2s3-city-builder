#ifndef _RULES_TERRAIN_HH_
#define _RULES_TERRAIN_HH_

#include "all_includes.hh"

class TerrainQuad : public Chose {
    private :
	Quad c;
	bool addTrees;

    public :
	TerrainQuad(Quad _c, bool _addTrees = true);
	virtual void split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

class TerrainTri : public Chose {
    private :
	Triangle c;
	bool addTrees;

    public :
	TerrainTri(Triangle _c, bool _addTrees = true);
	virtual void split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
