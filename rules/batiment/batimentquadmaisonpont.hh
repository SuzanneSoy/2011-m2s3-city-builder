#ifndef _RULES_BATIMENT_BATIMENTQUADMAISONPONT_HH_
#define _RULES_BATIMENT_BATIMENTQUADMAISONPONT_HH_

#include "all_includes.hh"


class BatimentQuadMaisonPont: public Chose {
    private :
	Quad c;
	int height;

    public :

	BatimentQuadMaisonPont(Quad c, int height);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
