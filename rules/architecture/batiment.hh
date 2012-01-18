#ifndef _RULES_ARCHITECTURE_BATIMENT_HH_
#define _RULES_ARCHITECTURE_BATIMENT_HH_

#include "all_includes.hh"

class BatimentQuad_ : public Chose {
	Quad c;
    bool isSub;
    bool we, ws, ww, wn;

    public:
	BatimentQuad_(Quad _c, bool _isSub=false, bool _we=true, bool _ws=true, bool _ww=true, bool _wn=true);
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
