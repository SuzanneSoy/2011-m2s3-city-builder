#include "all_includes.hh"

Arbre::Arbre(Vertex _start, Angle3D _rotation, float _length) : start(_start), rotation(_rotation), length(_length) {}

bool Arbre::split() {
	if (length < 5) return false;
	return false;
}

void Arbre::triangulation() {
	float radius = length/16;
	float limitLength = length;
	Vertex hTronc = rotation.h * length;
	Vertex uTronc = rotation.u * radius;
	Vertex lTronc = rotation.l * radius;
	Vertex hFeuillage = rotation.h * limitLength;
	Vertex uFeuillage = rotation.u * limitLength / 2;
	Vertex lFeuillage = rotation.l * limitLength / 2;
	Quad cTronc(start +uTronc +lTronc, start +uTronc -lTronc, start -uTronc -lTronc, start -uTronc +lTronc);
	addGPUOcto(cTronc, cTronc + hTronc, Couleurs::tronc);

	Quad cFeuillage(start +uFeuillage +lFeuillage, start +uFeuillage -lFeuillage, start -uFeuillage -lFeuillage, start -uFeuillage +lFeuillage);
	addGPUOcto(cFeuillage + hTronc, cFeuillage + hTronc + hFeuillage, Couleurs::feuillage);
}

void Arbre::getBoundingBoxPoints() {
	// TODO
	Vertex u = rotation.u * 100;
	Vertex l = rotation.l * 100;
	Quad c(start +u +l, start +u -l, start -u -l, start -u +l);
	addBBPoints(c);
}

void Arbre::branche() {

}

void Arbre::feuille() {

}
