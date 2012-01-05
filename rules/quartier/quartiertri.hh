#ifndef _RULES_QUARTIER_QUARTIERTRI_HH_
#define _RULES_QUARTIER_QUARTIERTRI_HH_

#include "all_includes.hh"


class QuartierTri : public Chose {
    public :
	Triangle c;

    public :
	QuartierTri(Triangle c);
	virtual bool split();
	virtual void triangulation();
	static Chose* factory(int seed, int n, Triangle c);
	virtual void getBoundingBoxPoints();
};

#endif
