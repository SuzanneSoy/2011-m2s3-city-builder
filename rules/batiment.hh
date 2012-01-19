#ifndef _RULES_BATIMENT_HH_
#define _RULES_BATIMENT_HH_

#include "all_includes.hh"

class BatimentQuad_ : public Chose {
private:
	Quad c;
	bool isSub;
	QuadBool w;
	void bordureRouteTrottoir();
	void sousBatiments();
	void etages();

public:
	BatimentQuad_(Quad _c, bool _isSub = false, QuadBool _w = QuadBool(true, true, true, true));
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
