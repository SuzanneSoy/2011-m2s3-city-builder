#ifndef _RULES_ARCHITECTURE_ARCHE_HH_
#define _RULES_ARCHITECTURE_ARCHE_HH_

#include "all_includes.hh"

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
private:
	 // TODO : couleur de l'arche
	static const char r = 0xF1;
	static const char g = 0xE0;
	static const char b = 0xE0;
};

#endif
