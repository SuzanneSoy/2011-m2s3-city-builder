#include "all_includes.hh"

BatimentQuadMaison::BatimentQuadMaison(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne, se, sw, nw);
	lctr = (ne + se + sw + nw) / 4;
    corner[NE] = ne;//-lctr;
	corner[SE] = se;//-lctr;
    corner[SW] = sw;//-lctr;
    corner[NW] = nw;//-lctr;
}

BatimentQuadMaison::~BatimentQuadMaison() {
    children.clear();
    triangles.clear();
}

void BatimentQuadMaison::getBoundingBoxPoints() {
	addBBPoint(corner[NE]);
	addBBPoint(corner[SE]);
	addBBPoint(corner[SW]);
	addBBPoint(corner[NW]);
	addBBPoint(corner[NE] + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
	addBBPoint(corner[SE] + Vertex(0,0,maxHeight + maxHeight/2));
	addBBPoint(corner[SW] + Vertex(0,0,maxHeight + maxHeight/2));
	addBBPoint(corner[NW] + Vertex(0,0,maxHeight + maxHeight/2));
}

bool BatimentQuadMaison::split() {
	return false;
}

void BatimentQuadMaison::triangulation() {
	triangles.reserve(12);

	int h = hashInRange(seed,0,minHeight,maxHeight);
	int htoit = hashInRange(seed,0,minHeight/2,maxHeight/2);
	Vertex neh = corner[NE] + Vertex(0,0,h);
	Vertex seh = corner[SE] + Vertex(0,0,h);
	Vertex nwh = corner[NW] + Vertex(0,0,h);
	Vertex swh = corner[SW] + Vertex(0,0,h);
	Vertex toit = (neh + seh + nwh + swh) / 4 + Vertex(0,0,htoit);

	// 4 Murs
	addQuad(/*lctr+*/neh,/*lctr+*/seh,/*lctr+*/corner[SE],/*lctr+*/corner[NE],0xf1,0xe3,0xad);
	addQuad(/*lctr+*/seh,/*lctr+*/swh,/*lctr+*/corner[SW],/*lctr+*/corner[SE],0xf1,0xe3,0xad);
	addQuad(/*lctr+*/swh,/*lctr+*/nwh,/*lctr+*/corner[NW],/*lctr+*/corner[SW],0xf1,0xe3,0xad);
	addQuad(/*lctr+*/nwh,/*lctr+*/neh,/*lctr+*/corner[NE],/*lctr+*/corner[NW],0xf1,0xe3,0xad);

	// 1 Toit
	addTriangle(new Triangle(/*lctr+*/neh,/*lctr+*/toit,/*lctr+*/seh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(/*lctr+*/seh,/*lctr+*/toit,/*lctr+*/swh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(/*lctr+*/swh,/*lctr+*/toit,/*lctr+*/nwh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(/*lctr+*/nwh,/*lctr+*/toit,/*lctr+*/neh,0x9a,0x48,0x3c));
}
