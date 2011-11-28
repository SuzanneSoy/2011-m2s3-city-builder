#include "all_includes.hh"

Chose::Chose() : seed(initialSeed), children() {}

std::ostream& operator<<(std::ostream& os, const Chose* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Chose& r) {
	(void)r; // unused
	return os << "Chose";
}

void Chose::addChild(Chose* c) {
	children.push_back(c);
	// TODO : Ajouter c dans une file d'attente des éléments pouvant être split.
}

void Chose::addTriangle(Triangle* t) {
	triangles.push_back(t);
	// TODO : Ajouter t dans la liste des triangles à envoyer au GPU.
}

void Chose::display() {
	if (children.size() > 0) {
		std::vector<Chose*>::iterator it;
		for (it = children.begin(); it != children.end(); ++it) {
			(*it)->display();
		}
	} else {
		std::vector<Triangle*>::iterator it;
		for (it = triangles.begin(); it != triangles.end(); ++it) {
			(*it)->display();
		}
	}
}
