#ifndef _RULES_ARCHE_HH_
#define _RULES_ARCHE_HH_

#include "all_includes.hh"

// Arche du nord au sud
class ArcheQuad : public Chose {
private:
	Quad c;
	float height;
	float start;
	float end;
public:
	ArcheQuad(Quad _c, float _height, float _start = 0, float _end = 1);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
	float f(float x);
	float ogive(float x);
	float berceau(float x);
};

#endif
