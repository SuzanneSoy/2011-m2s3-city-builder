#ifndef _RULES_QUAD_HERBE_HH_
#define _RULES_QUAD_HERBE_HH_

#include "all_includes.hh"


class TerrainQuadHerbe : public Chose {
    private :
	Quad c;

    public :
	TerrainQuadHerbe(Quad c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};


#endif
