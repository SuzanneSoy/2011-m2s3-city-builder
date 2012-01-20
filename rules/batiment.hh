#ifndef _RULES_BATIMENT_HH_
#define _RULES_BATIMENT_HH_

#include "all_includes.hh"

class BatimentQuad : public Chose {
private:
	Quad c;
	bool isSub;
	QuadBool w;
	void bordureRouteTrottoir();
	void sousBatiments();
	void etages();

public:
	BatimentQuad(Quad _c, bool _isSub = false, QuadBool _w = QuadBool(true, true, true, true));
	virtual void split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
	BatimentQuad* isSubdivision(bool val);
};

class BatimentTri : public Chose {
private:
	Triangle c;
	bool isSub;
	TriBool w;
	void bordureRouteTrottoir();
	void sousBatiments();
	void etages();

public:
	BatimentTri(Triangle _c, bool _isSub = false, TriBool _w = TriBool(true, true, true));
	virtual void split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
};

#endif
