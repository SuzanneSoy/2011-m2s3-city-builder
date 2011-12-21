#include "all_includes.hh"

BatimentQuadMaisonBlock::BatimentQuadMaisonBlock() {
}

BatimentQuadMaisonBlock::BatimentQuadMaisonBlock(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height) : Chose() {
	addEntropy(ne, se, sw, nw);
	lctr = Vertex(ne.x-nw.x,se.y-ne.y,0.0f);
    this->ne = ne-lctr;
    this->se = se-lctr;
    this-> sw = sw-lctr;
    this->nw = nw-lctr;
    this->height = height;
	triangulation();
}

BatimentQuadMaisonBlock::~BatimentQuadMaisonBlock() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
}

std::vector<Vertex*> BatimentQuadMaisonBlock::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
}

bool BatimentQuadMaisonBlock::split() {

	return true;
}

bool BatimentQuadMaisonBlock::merge() {
    for(unsigned int i = 0; i < children.size(); i++)
        delete(children[i]);
    children.clear();
    triangles.clear();
    return true;
}

void BatimentQuadMaisonBlock::triangulation() {
	//triangles.reserve(2);
    Vertex seh = se + Vertex(0,0,height);
    Vertex swh = sw + Vertex(0,0,height);
    Vertex nwh = nw + Vertex(0,0,height);
    Vertex neh = ne + Vertex(0,0,height);

    addOcto(lctr+se,lctr+sw,lctr+nw,lctr+ne,lctr+seh,lctr+swh,lctr+nwh,lctr+neh,0xFF,0x36,0x00);
}
