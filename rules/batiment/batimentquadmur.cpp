#include "all_includes.hh"

BatimentQuadMur::BatimentQuadMur(Quad c, float height) : Chose(), c(c), height(height) {
	addEntropy(c);
	this->window = false;
}

void BatimentQuadMur::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height));
}

void BatimentQuadMur::setWindow(Quad w) {
    this->windowPos = w;
    this->window = true;
}

bool BatimentQuadMur::split() {
    if(!window)
        return false;

    Quad left = c;
    Quad right = c;
    Quad top = c;
    Quad bottom = c;


    return true;
}

void BatimentQuadMur::triangulation() {
    //addGPUOcto(c, c + Vertex(0,0,height), 0xF1, 0xE0, 0xE0);
    addGPUOcto(c, c + Vertex(0,0,height), 0x60, 0x60, 0xFF);
}
