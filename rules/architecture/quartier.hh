#ifndef _RULES_ARCHITECTURE_QUARTIER_HH_
#define _RULES_ARCHITECTURE_QUARTIER_HH_

#include "all_includes.hh"

class QuartierQuad_: public Chose {
private:
	Quad c;
public:
	QuartierQuad_(Quad _c);
	virtual void getBoundingBoxPoints();
	virtual bool split();
	virtual void triangulation();
private:
	void concave();
	void angleAngle();
	void angleCote();
	void rect();
	void carre();
	void batiments();
};

class QuartierTri_: public Chose {
private:
	Triangle c;
public:
	QuartierTri_(Triangle _c);
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
