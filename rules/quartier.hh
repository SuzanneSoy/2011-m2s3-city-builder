#ifndef _RULES_QUARTIER_HH_
#define _RULES_QUARTIER_HH_

#include "all_includes.hh"

class QuartierQuad: public Chose {
private:
	Quad c;
public:
	QuartierQuad(Quad _c);
	virtual void getBoundingBoxPoints();
	virtual bool split();
	virtual void triangulation();
private:
	void triangulationConcave(Triangle t);
	void concave();
	void angleAngle();
	void angleCote();
	void rect();
	void carre();
	void longueRue();
};

class QuartierTri: public Chose {
private:
	Triangle c;
public:
	QuartierTri(Triangle _c);
	virtual void getBoundingBoxPoints();
	virtual bool split();
	virtual void triangulation();
private:
	void centre();
	void hauteur();
	void trapeze();
	void batiments();
};

#endif
