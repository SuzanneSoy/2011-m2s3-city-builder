#include "all_includes.hh"

Chose::Chose() : seed(initialSeed), children() {}

void Chose::addChild(Chose* c) {
	children.push_back(c);
}

void Chose::addTriangle(Triangle* t) {
	triangles.push_back(t);
}

void Chose::merge() {
	triangles.clear();
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

unsigned int Chose::initialSeed = random_seed();
