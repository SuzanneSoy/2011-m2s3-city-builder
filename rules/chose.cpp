#include "all_includes.hh"

Chose::Chose() : seed(initialSeed) {}

std::ostream& operator<<(std::ostream& os, const Chose* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Chose& r) {
	(void)r; // unused
	return os << "Chose";
}

void Chose::addChild(Chose* c) {
	children.insert(children.end(), c);
	// TODO : Ajouter c dans une file d'attente des éléments pouvant être split.
}

void Chose::addTriangle(Triangle* t) {
	triangles.insert(triangles.end(), t);
	// TODO : Ajouter t dans la liste des triangles à envoyer au GPU.
}
