#ifndef _RULES_BATIMENTMAISON_HH_
#define _RULES_BATIMENTMAISON_HH_

#include "all_includes.hh"


class BatimentQuadMaison : public Chose {
    private :
	Quad c;

    public :
	static const int minHeight = 400;
	static const int maxHeight = 800;

	BatimentQuadMaison(Quad c);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
