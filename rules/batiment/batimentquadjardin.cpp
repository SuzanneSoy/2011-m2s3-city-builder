#include "all_includes.hh"

BatimentQuadJardin::BatimentQuadJardin(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose() {
	addEntropy(ne, se, sw, nw);
	c[NE] = ne;
	c[SE] = se;
    c[SW] = sw;
    c[NW] = nw;
}

BatimentQuadJardin::~BatimentQuadJardin() {
    children.clear();
    triangles.clear();
}

void BatimentQuadJardin::getBoundingBoxPoints() {
	addBBPoint(c[NE]);
	addBBPoint(c[SE]);
	addBBPoint(c[SW]);
	addBBPoint(c[NW]);
	addBBPoint(c[NE] + Vertex(0,0,200)); // TODO
	addBBPoint(c[SE] + Vertex(0,0,200));
	addBBPoint(c[SW] + Vertex(0,0,200));
	addBBPoint(c[NW] + Vertex(0,0,200));
}

bool BatimentQuadJardin::split() {
	return false;
}

void BatimentQuadJardin::triangulation() {
	triangles.reserve(2);

	addTriangle(new GPUTriangle(/*lctr+*/c[NE],/*lctr+*/c[NW],/*lctr+*/c[SW],0x12,0x64,0x12));
	addTriangle(new GPUTriangle(/*lctr+*/c[SW],/*lctr+*/c[SE],/*lctr+*/c[NE],0x12,0x64,0x12));
}
