#ifndef _RULES_ARCHITECTURE_ARBRE_HH_
#define _RULES_ARCHITECTURE_ARBRE_HH_

#include "all_includes.hh"

class Arbre : public Chose {
private:
	Vertex start;
	Angle3D rotation;
	float length;
public:
	Arbre(Vertex _start, Angle3D _rotation, float _length);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
	void branche();
	void feuille();
};

#endif
