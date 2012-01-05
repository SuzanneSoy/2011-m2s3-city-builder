#ifndef _RULES_BATIMENT_BATIMENTTRI_HH_
#define _RULES_BATIMENT_BATIMENTTRI_HH_

#include "all_includes.hh"


class BatimentTri : public Chose {
    private :
	Triangle c;

    public :
	static const int minHeight = 400;
	static const int maxHeight = 800;

	BatimentTri(Triangle c);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
