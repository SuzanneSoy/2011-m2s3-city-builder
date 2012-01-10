#include "all_includes.hh"

TerrainTriHerbe::TerrainTriHerbe(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

void TerrainTriHerbe::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,1000)); // TODO
}

void TerrainTriHerbe::triangulation() {
	addGPUTriangle(c, 0x11, 0xaa, 0x22);
}
