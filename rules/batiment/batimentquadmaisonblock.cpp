#include "all_includes.hh"

BatimentQuadMaisonBlock::BatimentQuadMaisonBlock(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height) : Chose() {
	addEntropy(ne, se, sw, nw);
	lctr = Vertex(ne.x-nw.x,se.y-ne.y,0.0f);
    this->ne = ne-lctr;
    this->se = se-lctr;
    this-> sw = sw-lctr;
    this->nw = nw-lctr;
    this->height = height;
}

BatimentQuadMaisonBlock::~BatimentQuadMaisonBlock() {
    children.clear();
    triangles.clear();
}

void BatimentQuadMaisonBlock::getBoundingBoxPoints() {
	// TODO
}

bool BatimentQuadMaisonBlock::split() {
	return false;
}

void BatimentQuadMaisonBlock::triangulation() {
	//triangles.reserve(2);
    Vertex seh = se + Vertex(0,0,height);
    Vertex swh = sw + Vertex(0,0,height);
    Vertex nwh = nw + Vertex(0,0,height);
    Vertex neh = ne + Vertex(0,0,height);

    addOcto(lctr+se,lctr+sw,lctr+nw,lctr+ne,lctr+seh,lctr+swh,lctr+nwh,lctr+neh,0xFF,0x36,0x00);
}
