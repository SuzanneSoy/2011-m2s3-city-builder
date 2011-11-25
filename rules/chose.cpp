#include "all_includes.hh"

Chose::Chose() : seed(initialSeed) {}

std::ostream& operator<<(std::ostream& os, const Chose* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Chose& r) {
	(void)r; // unused
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
	// TODO : Ajouter c dans une file d'attente des éléments pouvant être split.
}

void Chose::addTriangle(Triangle* t) {
	triangles.push_back(t);
	// TODO : Ajouter t dans la liste des triangles à envoyer au GPU.
}
