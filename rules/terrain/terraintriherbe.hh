#ifndef _RULES_TERRAIN_TERRAINTRIHERBE_HH_
#define _RULES_TERRAIN_TERRAINTRIHERBE_HH_

#include "all_includes.hh"


class TerrainTriHerbe : public Chose {
    private :
	Triangle c;

    public :
	TerrainTriHerbe(Triangle _c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};


#endif
