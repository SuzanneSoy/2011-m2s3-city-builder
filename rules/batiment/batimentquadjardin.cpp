#include "all_includes.hh"

BatimentQuadJardin::BatimentQuadJardin(Quad c) : Chose(), c(c) {
	addEntropy(c);
}

void BatimentQuadJardin::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,200)); // TODO
}

void BatimentQuadJardin::triangulation() {
	triangles.reserve(2);

	addGPUQuad(c, 0x12, 0x64, 0x12);
}
