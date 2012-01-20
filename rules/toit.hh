#ifndef _RULES_TOIT_HH_
#define _RULES_TOIT_HH_

#include "all_includes.hh"

class ToitQuad : public Chose {
private:
	Quad c;
	float height;
public:
	ToitQuad(Quad _c, float _height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
private:
	void pointCentral();
	void quatrePoints();
	void deuxPoints();
	void deuxPointsVerticaux();
	void plat();
};

class ToitTri : public Chose {
private:
	Triangle c;
	float height;
public:
	ToitTri(Triangle _c, float _height);
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
private:
	void pointCentral();
	void troisPoints();
	void unPointVertical();
	void deuxPointsVerticaux();
	void plat();
};

#endif
