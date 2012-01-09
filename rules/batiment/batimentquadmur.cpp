#include "all_includes.hh"

BatimentQuadMur::BatimentQuadMur(Quad c, float height) : Chose(), c(c), height(height) {
	addEntropy(c);
}

void BatimentQuadMur::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height));
}

void BatimentQuadMur::triangulation() {
    addGPUOcto(c, c + Vertex(0,0,height), 0xF1, 0xE0, 0xE0);
}
