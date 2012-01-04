#ifndef _RULES_BATIMENTMAISONBLOCK_HH_
#define _RULES_BATIMENTMAISONBLOCK_HH_

#include "all_includes.hh"


class BatimentQuadBlock : public Chose {
    private :
	Quad c;
	int height;

    public :
	BatimentQuadBlock(Quad c, int height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
