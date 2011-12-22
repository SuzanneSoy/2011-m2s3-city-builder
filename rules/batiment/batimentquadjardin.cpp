#include "all_includes.hh"

BatimentQuadJardin::BatimentQuadJardin(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne, se, sw, nw);
	lctr = (ne + se + sw + nw) / 4;
    corner[NE] = ne;//-lctr;
	corner[SE] = se;//-lctr;
    corner[SW] = sw;//-lctr;
    corner[NW] = nw;//-lctr;
}

BatimentQuadJardin::~BatimentQuadJardin() {
    children.clear();
    triangles.clear();
}

void BatimentQuadJardin::getBoundingBoxPoints() {
	addBBPoint(corner[NE]);
	addBBPoint(corner[SE]);
	addBBPoint(corner[SW]);
	addBBPoint(corner[NW]);
	addBBPoint(corner[NE] + Vertex(0,0,200)); // TODO
	addBBPoint(corner[SE] + Vertex(0,0,200));
	addBBPoint(corner[SW] + Vertex(0,0,200));
	addBBPoint(corner[NW] + Vertex(0,0,200));
}

bool BatimentQuadJardin::split() {
	return false;
}

void BatimentQuadJardin::triangulation() {
	triangles.reserve(2);

	addTriangle(new Triangle(/*lctr+*/corner[NE],/*lctr+*/corner[NW],/*lctr+*/corner[SW],0x12,0x64,0x12));
	addTriangle(new Triangle(/*lctr+*/corner[SW],/*lctr+*/corner[SE],/*lctr+*/corner[NE],0x12,0x64,0x12));
}
