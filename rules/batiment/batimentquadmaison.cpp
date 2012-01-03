#include "all_includes.hh"

BatimentQuadMaison::BatimentQuadMaison(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne, se, sw, nw);
	c[NE] = ne;
	c[SE] = se;
    c[SW] = sw;
    c[NW] = nw;
}

BatimentQuadMaison::~BatimentQuadMaison() {
    children.clear();
    triangles.clear();
}

void BatimentQuadMaison::getBoundingBoxPoints() {
	addBBPoint(c[NE]);
	addBBPoint(c[SE]);
	addBBPoint(c[SW]);
	addBBPoint(c[NW]);
	addBBPoint(c[NE] + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
	addBBPoint(c[SE] + Vertex(0,0,maxHeight + maxHeight/2));
	addBBPoint(c[SW] + Vertex(0,0,maxHeight + maxHeight/2));
	addBBPoint(c[NW] + Vertex(0,0,maxHeight + maxHeight/2));
}

bool BatimentQuadMaison::split() {
	return false;
}

void BatimentQuadMaison::triangulation() {
	triangles.reserve(12);

	int h = hashInRange(seed,0,minHeight,maxHeight);
	int htoit = hashInRange(seed,0,minHeight/2,maxHeight/2);
	Vertex neh = c[NE] + Vertex(0,0,h);
	Vertex seh = c[SE] + Vertex(0,0,h);
	Vertex nwh = c[NW] + Vertex(0,0,h);
	Vertex swh = c[SW] + Vertex(0,0,h);
	Vertex toit = (neh + seh + nwh + swh) / 4 + Vertex(0,0,htoit);

	// 4 Murs
	addQuad(/*lctr+*/neh,/*lctr+*/seh,/*lctr+*/c[SE],/*lctr+*/c[NE],0xf1,0xe3,0xad);
	addQuad(/*lctr+*/seh,/*lctr+*/swh,/*lctr+*/c[SW],/*lctr+*/c[SE],0xf1,0xe3,0xad);
	addQuad(/*lctr+*/swh,/*lctr+*/nwh,/*lctr+*/c[NW],/*lctr+*/c[SW],0xf1,0xe3,0xad);
	addQuad(/*lctr+*/nwh,/*lctr+*/neh,/*lctr+*/c[NE],/*lctr+*/c[NW],0xf1,0xe3,0xad);

	// 1 Toit
	addTriangle(new GPUTriangle(/*lctr+*/neh,/*lctr+*/toit,/*lctr+*/seh,0x96,0x16,0x18));
	addTriangle(new GPUTriangle(/*lctr+*/seh,/*lctr+*/toit,/*lctr+*/swh,0x96,0x16,0x18));
	addTriangle(new GPUTriangle(/*lctr+*/swh,/*lctr+*/toit,/*lctr+*/nwh,0x96,0x16,0x18));
	addTriangle(new GPUTriangle(/*lctr+*/nwh,/*lctr+*/toit,/*lctr+*/neh,0x96,0x16,0x18));
}
