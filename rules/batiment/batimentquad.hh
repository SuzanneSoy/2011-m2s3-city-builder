#ifndef _RULES_BATIMENT_BATIMENTQUAD_HH_
#define _RULES_BATIMENT_BATIMENTQUAD_HH_

#include "all_includes.hh"


class BatimentQuad : public Chose {
    private :
	Quad c;

    public :
	static const int minHeight = 400;
	static const int maxHeight = 800;

	BatimentQuad(Quad c);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
