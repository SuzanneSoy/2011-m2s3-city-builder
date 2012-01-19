#ifndef _RULES_ARCHE_HH_
#define _RULES_ARCHE_HH_

#include "all_includes.hh"

// Arche du nord au sud
class ArcheQuad : public Chose {
private:
	enum Type {
		RANDOM,
		OGIVE,
		BERCEAU,
		PLAT
	};
	Quad c;
	float height;
	float start;
	float end;
	Type type;
public:
	ArcheQuad(Quad _c, float _height, float _start = 0, float _end = 1, Type _type = RANDOM);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
	float f(float x);
};

#endif
