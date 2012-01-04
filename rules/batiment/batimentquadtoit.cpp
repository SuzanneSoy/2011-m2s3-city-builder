#include "all_includes.hh"

BatimentQuadToit::BatimentQuadToit(Quad c, int height) : Chose(), c(c), height(height) {
	addEntropy(c);
}

void BatimentQuadToit::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

void BatimentQuadToit::triangulation() {
	//triangles.reserve(2);
    Vertex ce = c[SE] + (c[NE] - c[SE])/2 + Vertex(0,0,height/3.);
    Vertex cw = c[SW] + (c[NW] - c[SW])/2 + Vertex(0,0,height/3.);

    addTriangle(new GPUTriangle(c[SW],c[NW],cw,0xF1,0xE0,0xE0));
    addTriangle(new GPUTriangle(c[NE],c[SE],ce,0xF1,0xE0,0xE0));

    addQuad(c[NE],c[NW],cw,ce,0xE0,0x20,0x00);
    addQuad(c[SW],c[SE],ce,cw,0xE0,0x20,0x00);
}
