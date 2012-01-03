#include "all_includes.hh"

BatimentQuadToit::BatimentQuadToit(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height) : Chose() {
	addEntropy(ne, se, sw, nw);
    c[NE] = ne;
    c[SE] = se;
    c[SW] = sw;
    c[NW] = nw;
    this->height = height;
}

BatimentQuadToit::~BatimentQuadToit() {
    children.clear();
    triangles.clear();
}

void BatimentQuadToit::getBoundingBoxPoints() {
	addBBPoint(c[NE]);
	addBBPoint(c[SE]);
	addBBPoint(c[SW]);
	addBBPoint(c[NW]);
	addBBPoint(c[NE] + Vertex(0,0,height)); // TODO
	addBBPoint(c[SE] + Vertex(0,0,height));
	addBBPoint(c[SW] + Vertex(0,0,height));
	addBBPoint(c[NW] + Vertex(0,0,height));
}

bool BatimentQuadToit::split() {
	return false;
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
