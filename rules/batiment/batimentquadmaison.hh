#ifndef _RULES_BATIMENT_BATIMENTQUADMAISON_HH_
#define _RULES_BATIMENT_BATIMENTQUADMAISON_HH_

#include "all_includes.hh"


class BatimentQuadMaison : public Chose {
    private :
	Quad c;

    public :
	static const int minHeight = 250;
	static const int maxHeight = 350;

	BatimentQuadMaison(Quad c);
	virtual void triangulation();
	virtual bool split();
	virtual void getBoundingBoxPoints();
};

#endif
