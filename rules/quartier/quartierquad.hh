#ifndef _RULES_QUADRILATERE_HH_
#define _RULES_QUADRILATERE_HH_

#include "all_includes.hh"


class QuartierQuad : public Chose {
public:
	Quad c;
public:
	QuartierQuad(Quad c);
	virtual bool split();
	virtual void triangulation();
	static Chose* factory(int seed, int n, Quad c);
	virtual void getBoundingBoxPoints();
};

#endif
