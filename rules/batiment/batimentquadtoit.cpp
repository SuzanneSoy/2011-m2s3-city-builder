#include "all_includes.hh"

BatimentQuadToit::BatimentQuadToit(Quad c, float height) : Chose(), c(c), height(height) {
	addEntropy(c);
}

void BatimentQuadToit::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

void BatimentQuadToit::triangulation() {
    Vertex ce = c[SE] + (c[NE] - c[SE])/2 + Vertex(0,0,height / 3.f);
    Vertex cw = c[SW] + (c[NW] - c[SW])/2 + Vertex(0,0,height / 3.f);

    addGPUTriangle(c[NW],cw,c[SW],0xF1,0xE0,0xE0);
    addGPUTriangle(c[SE],ce,c[NE],0xF1,0xE0,0xE0);

    addGPUQuad(c[NE],c[NW],cw,ce,0xE0,0x20,0x00);
    addGPUQuad(c[SW],c[SE],ce,cw,0xE0,0x20,0x00);
}
