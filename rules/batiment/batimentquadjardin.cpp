#include "all_includes.hh"

BatimentQuadJardin::BatimentQuadJardin(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
	addEntropy(ne, se, sw, nw);
	triangulation();
}

int BatimentQuadJardin::width() { return this->ne.x - this->sw.x; }

int BatimentQuadJardin::height() { return this->ne.y - this->sw.y; }

std::vector<Vertex*> BatimentQuadJardin::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
}

bool BatimentQuadJardin::subdivide() {

	return true;
}

void BatimentQuadJardin::triangulation() {
	triangles.reserve(2);

	addTriangle(new Triangle(ne,nw,sw,0x12,0x64,0x12));
	addTriangle(new Triangle(sw,se,ne,0x10,0x60,0x10));
}
