#ifndef _RULES_ARCHITECTURE_BATIMENT_HH_
#define _RULES_ARCHITECTURE_BATIMENT_HH_

#include "all_includes.hh"

class BatimentQuad_ : public Chose {
	Quad c;
    bool isSub;

    public:
	BatimentQuad_(Quad _c);
	BatimentQuad_(Quad _c, bool _isSub);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
	BatimentQuad_* isSubdivision(bool val);
};

class BatimentTri_ : public Chose {
	Triangle c;

    public:
	BatimentTri_(Triangle _c);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
