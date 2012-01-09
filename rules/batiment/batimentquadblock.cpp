#include "all_includes.hh"

BatimentQuadBlock::BatimentQuadBlock(Quad c, float height) : Chose(), c(c), height(height) {
	addEntropy(c);
}

void BatimentQuadBlock::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

bool BatimentQuadBlock::split() {
    Quad me = c;
    Quad ms = c;
    Quad mw = c;
    Quad mn = c;

    me[NW] = me[NE] + ((me[NW] - me[NW]) / me.length(N))*150;
    //TODO les autres côtés.
    return false;
}

void BatimentQuadBlock::triangulation() {
    addGPUOcto(c, c + Vertex(0,0,height), 0xF1, 0xE0, 0xE0);
}
