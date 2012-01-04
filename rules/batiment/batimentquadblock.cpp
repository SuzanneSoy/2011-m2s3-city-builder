#include "all_includes.hh"

BatimentQuadBlock::BatimentQuadBlock(Quad c, int height) : Chose(), c(c), height(height) {
	addEntropy(c);
}

void BatimentQuadBlock::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

void BatimentQuadBlock::triangulation() {
    addGPUOcto(c, c + Vertex(0,0,height), 0xF1, 0xE0, 0xE0);
}
