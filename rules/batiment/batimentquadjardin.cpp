#include "all_includes.hh"

BatimentQuadJardin::BatimentQuadJardin(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne, se, sw, nw);
	lctr = Vertex(ne.x-nw.x,se.y-ne.y,0.0f);
    this->ne = ne-lctr;
    this->se = se-lctr;
    this-> sw = sw-lctr;
    this->nw = nw-lctr;
	triangulation();
}

BatimentQuadJardin::~BatimentQuadJardin() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
}

int BatimentQuadJardin::width() { return this->ne.x - this->sw.x; }

int BatimentQuadJardin::height() { return this->ne.y - this->sw.y; }

std::vector<Vertex*> BatimentQuadJardin::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
}

bool BatimentQuadJardin::split() {

	return true;
}

bool BatimentQuadJardin::merge() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
    return true;
}

void BatimentQuadJardin::triangulation() {
	triangles.reserve(2);

	addTriangle(new Triangle(lctr+ne,lctr+nw,lctr+sw,0x12,0x64,0x12));
	addTriangle(new Triangle(lctr+sw,lctr+se,lctr+ne,0x12,0x64,0x12));

	//addTriangle(new Triangle(lctr+ne,lctr+nw,lctr+sw,0xFF,0xFF,0x00));
	//addTriangle(new Triangle(lctr+sw,lctr+se,lctr+ne,0xFF,0xFF,0x00));
}
