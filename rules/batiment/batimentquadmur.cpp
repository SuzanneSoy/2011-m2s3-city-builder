#include "all_includes.hh"

BatimentQuadMur::BatimentQuadMur(Quad _c, Quad _ch) : Chose(), c(_c), ch(_ch) {
	addEntropy(c);
	addEntropy(ch);
	this->window = false;
}

void BatimentQuadMur::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(ch);
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

    //addChild(BatimentQuadMur())

    return false;
}

void BatimentQuadMur::triangulation() {
    addGPUOcto(c, ch, 0xf1,0xe3,0xad);
}
