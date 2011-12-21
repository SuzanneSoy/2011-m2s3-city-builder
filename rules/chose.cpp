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

void Chose::addQuad(Vertex u, Vertex v, Vertex w, Vertex x, char r, char g, char b) {
    this->addTriangle(new Triangle(u,x,w,r,g,b));
    this->addTriangle(new Triangle(w,v,u,r,g,b));
}

void Chose::addOcto(Vertex a, Vertex b, Vertex c, Vertex d,
                    Vertex e, Vertex f, Vertex g, Vertex h, char red, char green, char blue) {
    this->addQuad(a,b,c,d,red,green,blue);
    this->addQuad(e,f,g,h,red,green,blue);
    this->addQuad(b,a,e,f,red,green,blue);
    this->addQuad(c,b,f,g,red,green,blue);
    this->addQuad(d,c,g,h,red,green,blue);
    this->addQuad(a,d,h,e,red,green,blue);
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
