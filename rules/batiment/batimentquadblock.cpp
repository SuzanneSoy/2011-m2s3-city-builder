#include "all_includes.hh"

BatimentQuadBlock::BatimentQuadBlock(Vertex ne, Vertex se, Vertex sw, Vertex nw, int height) : Chose() {
	addEntropy(ne, se, sw, nw);
	lctr = Vertex(ne.x-nw.x,se.y-ne.y,0.0f);
    c[NE] = ne;
    c[SE] = se;
    c[SW] = sw;
    c[NW] = nw;
    this->height = height;
}

BatimentQuadBlock::~BatimentQuadBlock() {
    children.clear();
    triangles.clear();
}

void BatimentQuadBlock::getBoundingBoxPoints() {
	addBBPoint(c[NE]);
	addBBPoint(c[SE]);
	addBBPoint(c[SW]);
	addBBPoint(c[NW]);
	addBBPoint(c[NE] + Vertex(0,0,height)); // TODO
	addBBPoint(c[SE] + Vertex(0,0,height));
	addBBPoint(c[SW] + Vertex(0,0,height));
	addBBPoint(c[NW] + Vertex(0,0,height));// TODO
}

bool BatimentQuadBlock::split() {
	return false;
}

void BatimentQuadBlock::triangulation() {
	//triangles.reserve(2);
    Vertex seh = c[SE] + Vertex(0,0,height);
    Vertex swh = c[SW] + Vertex(0,0,height);
    Vertex nwh = c[NW] + Vertex(0,0,height);
    Vertex neh = c[NE] + Vertex(0,0,height);

    addOcto(c[SE],c[SW],c[NW],c[NE],seh,swh,nwh,neh,0xFF,0x36,0x00);
}
