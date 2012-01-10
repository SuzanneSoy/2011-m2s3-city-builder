#include "all_includes.hh"

TerrainQuadHerbe::TerrainQuadHerbe(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void TerrainQuadHerbe::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,1000)); // TODO
}

void TerrainQuadHerbe::triangulation() {
	triangles.reserve(2);
	addGPUQuad(c, 0x11, 0xaa, 0x22);
}
