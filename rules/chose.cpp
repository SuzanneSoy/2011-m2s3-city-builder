#include "all_includes.hh"

Chose::Chose() : seed(initialSeed) {}

std::ostream& operator<<(std::ostream& os, const Chose* c) {
	return os << *c;
}

std::ostream& operator<<(std::ostream& os, const Chose& c) {
	(void)c; // unused
	return os << "Chose";
}

void Chose::initChildren(int n) {
	children = std::vector<Chose*>(n);
}

void Chose::initTriangles(int n) {
	triangles = std::vector<Triangle*>(n);
}

void Chose::addChild(Chose* c) {
	children.push_back(c);
}

void Chose::use() {
	// Lorsqu'on utilise une Chose c, on la split d'abbord (on
	// n'utilisera pas les fils tout de suite, donc pas de récursion).
	subdivide();
	gainErrorSurfacePerTriangle = errorSurfacePerTriangle;
	std::vector<Chose*>::iterator it;
	for (it = children.begin(); it != children.end(); ++it) {
		gainErrorSurfacePerTriangle -= it->errorSurfacePerTriangle);
	}
	// TODO : isLeaf = true;
}

void Chose::unuse() {
	// TODO : isLeaf = false;
}

void Chose::addTriangle(Triangle* t) {
	triangles.push_back(t);
}

void Chose::setErrorVolume(int errorVolume) {
	// Calcul d'une approximation de la surface d'erreur à l'écran, en
	// considérant que l'objet est en fait juste une texture plaquée
	// sur un plan perpendiculaire au sol et parallèle à l'écran.
	errorSurfacePerTriangle = pow((float)errorVolume / (float)triangles.size(), 2.f/3.f);
}

// int Chose::gainScreenSurfacePerTriangle(Vertex camera) {
int Chose::gainScreenSurfacePerTriangle(Vertex camera) {
	int frontFrustumDist = 1; // TODO : valeur bidon.
	// Surface de la projection à l'écran de la surface d'erreur :
	return (int)(gainErrorSurfacePerTriangle * (frontFrustumDist * frontFrustumDist) / (distance * distance));
}
