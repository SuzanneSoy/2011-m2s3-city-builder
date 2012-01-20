#include "all_includes.hh"

void Arbre::initPlane(Vertex _start, Triangle plane) {
	start = _start;
	type = ARBRE;
	addEntropy(start);
	addEntropy(plane);

	Vertex h = plane.normalizedNormal();
	Vertex l = (plane[TOP] - plane[LEFT]).normalize();
	Vertex u = h * l;

	rotation = Angle3D(h, l, u);
	rotation = rotation.rotateH(floatInRange(seed, -3, 0, 2*Angle::Pi));
	rotation = rotation.rotateU(floatInRange(seed, -4, Angle::d2r(-10), Angle::d2r(10)));
	length = floatInRange(seed, -5, 3*100, 4*100);
}

Arbre::Arbre(Vertex _start, Triangle plane) {
	initPlane(_start, plane);
}

Arbre::Arbre(Vertex _start, Quad plane) {
	initPlane(_start, Triangle(plane[NE], plane[SE], plane[SW]));
}

Arbre::Arbre(Vertex _start, Angle3D _rotation, float _length, Type _type) : start(_start), rotation(_rotation), length(_length), type(_type) {
	addEntropy(start, rotation.h, rotation.l, rotation.u);
	addEntropyf(length);
	addEntropy((int)(type));
}

void Arbre::split() {
	if (type == ARBRE && length > floatInRange(seed, -1, 10, 20)) {
		int nbBranches = 2 + (hash2(seed, -2) % 3);
		for (int i = 0; i < nbBranches; i++) {
			Vertex bStart = end(floatInRange(seed, 4*i, 0.7f, 0.9f));
			Angle3D rot = rotation;
			rot = rot.rotateH(Angle::d2r(floatInRange(seed, 4*i+1, 25.f, 37.f) + (float)i*(360.f / (float)nbBranches)));
			rot = rot.rotateU(Angle::d2r(floatInRange(seed, 4*i+2, 35.f, 55.f)));
			float len = length * floatInRange(seed, 4*i+3, tauxMax()*2.f/3.f, tauxMax());
			addChild(new Arbre(bStart, rot, len, ARBRE));
		}
		addChild(new Arbre(start, rotation, length, TRONC));
	}
}

void Arbre::triangulation() {
	if (type == ARBRE || type == TRONC) tronc();
	if (type == ARBRE) feuille();
}

void Arbre::getBoundingBoxPoints() {
	// TODO
	Vertex u = rotation.u * limitLength() / 2.f;
	Vertex l = rotation.l * limitLength() / 2.f;
	Quad c(start +u +l, start -u +l, start -u -l, start +u -l);
	addBBPoints(c, length + limitLength());
}

float Arbre::LODFactor() {
	return 4.f;
}

Vertex Arbre::end(float position) const {
	return (start + rotation.h * length * position);
}

float Arbre::tauxMax() {
	return 0.6f;
}
const float Arbre::limitLengthFactor = calcLimitLengthFactor();
float Arbre::calcLimitLengthFactor() {
	float limit = 0;
	for (float i = 1; i > 0.001; i = i * tauxMax())
		limit += i;
	return limit - 1;
}

float Arbre::limitLength() const {
	return length * limitLengthFactor;
}

float Arbre::maxRadius(float length) {
	return length * (1+limitLengthFactor);
}

void Arbre::tronc() {
	float radius = length/16;
	Vertex hTronc = end(1.f) - start;
	Vertex uTronc = rotation.u * radius;
	Vertex lTronc = rotation.l * radius;
	Quad cTronc(start +uTronc +lTronc, start -uTronc +lTronc, start -uTronc -lTronc, start +uTronc -lTronc);
	addGPUQuad(cTronc + hTronc, Couleurs::tronc);
	addGPUFourQuads(cTronc, cTronc + hTronc, Couleurs::tronc);
}

void Arbre::feuille() {
	Vertex hFeuillage = rotation.h * limitLength();
	Vertex uFeuillage = rotation.u * limitLength() / 2.f;
	Vertex lFeuillage = rotation.l * limitLength() / 2.f;
	Vertex startFeuillage = end(1.f);

	unsigned int c = Couleurs::feuillage;
	if (length < 20 && proba(seed, 12345, 0.04f))
		c = Couleurs::pomme;

	Quad cFeuillage(startFeuillage +uFeuillage +lFeuillage, startFeuillage -uFeuillage +lFeuillage, startFeuillage -uFeuillage -lFeuillage, startFeuillage +uFeuillage -lFeuillage);
	addGPUOcto(cFeuillage, cFeuillage + hFeuillage, c);
}
