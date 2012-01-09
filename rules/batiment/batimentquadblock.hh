#ifndef _RULES_BATIMENT_BATIMENTQUADBLOCK_HH_
#define _RULES_BATIMENT_BATIMENTQUADBLOCK_HH_

#include "all_includes.hh"


class BatimentQuadBlock : public Chose {
    private :
	Quad c;
	float height;

    public :
	BatimentQuadBlock(Quad c, float height);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
