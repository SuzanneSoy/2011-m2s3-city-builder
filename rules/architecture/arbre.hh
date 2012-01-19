#ifndef _RULES_ARCHITECTURE_ARBRE_HH_
#define _RULES_ARCHITECTURE_ARBRE_HH_

#include "all_includes.hh"

class Arbre : public Chose {
public:
	enum Type {
		ARBRE,
		TRONC
	};
private:
	Vertex start;
	Angle3D rotation;
	float length;
	Type type;
	Vertex end(float position) const;
	float limitLength() const;
	static float tauxMax();
	static float calcLimitLengthFactor();
	static const float limitLengthFactor;
public:
	Arbre(Vertex _start, Angle3D _rotation, float _length, Type _type = ARBRE);
	virtual bool split();
	virtual void triangulation();
	virtual void getBoundingBoxPoints();
	virtual float LODFactor();
	void tronc();
	void feuille();
};

#endif
