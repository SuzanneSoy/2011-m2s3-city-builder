#include "all_includes.hh"

BatimentQuadMaison::BatimentQuadMaison(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne, se, sw, nw);
	lctr = Vertex(ne.x-nw.x,se.y-ne.y,0.0f);
    this->ne = ne-lctr;
    this->se = se-lctr;
    this-> sw = sw-lctr;
    this->nw = nw-lctr;
	triangulation();
}

BatimentQuadMaison::~BatimentQuadMaison() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
}

int BatimentQuadMaison::width() { return this->ne.x - this->sw.x; }

int BatimentQuadMaison::height() { return this->ne.y - this->sw.y; }

std::vector<Vertex*> BatimentQuadMaison::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
}

bool BatimentQuadMaison::split() {

	return true;
}

void BatimentQuadMaison::triangulation() {
	triangles.reserve(12);

	int h = hashInRange(seed,0,minHeight,maxHeight);
	int htoit = hashInRange(seed,0,minHeight/2,maxHeight/2);
	Vertex neh = ne + Vertex(0,0,h);
	Vertex seh = se + Vertex(0,0,h);
	Vertex nwh = nw + Vertex(0,0,h);
	Vertex swh = sw + Vertex(0,0,h);
	Vertex toit = (neh + seh + nwh + swh) / 4 + Vertex(0,0,htoit);

	// 4 Murs
	addTriangle(new Triangle(lctr+neh,lctr+seh,lctr+ne,0xf1,0xe3,0xad)); addTriangle(new Triangle(lctr+seh,lctr+se,lctr+ne,0xf1,0xe3,0xad)); // ne-se-seh-neh
	addTriangle(new Triangle(lctr+seh,lctr+swh,lctr+se,0xf1,0xe3,0xad)); addTriangle(new Triangle(lctr+swh,lctr+sw,lctr+se,0xf1,0xe3,0xad)); // se-sw-swh-seh
	addTriangle(new Triangle(lctr+swh,lctr+nwh,lctr+sw,0xf1,0xe3,0xad)); addTriangle(new Triangle(lctr+nwh,lctr+nw,lctr+sw,0xf1,0xe3,0xad)); // sw-nw-nwh-swh
	addTriangle(new Triangle(lctr+nwh,lctr+neh,lctr+nw,0xf1,0xe3,0xad)); addTriangle(new Triangle(lctr+neh,lctr+ne,lctr+nw,0xf1,0xe3,0xad)); // nw-ne-neh-nwh

	// 1 Toit
	addTriangle(new Triangle(lctr+neh,lctr+toit,lctr+seh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(lctr+seh,lctr+toit,lctr+swh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(lctr+swh,lctr+toit,lctr+nwh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(lctr+nwh,lctr+toit,lctr+neh,0x9a,0x48,0x3c));
}
