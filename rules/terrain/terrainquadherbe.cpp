#include "all_includes.hh"

TerrainQuadHerbe::TerrainQuadHerbe(Quad c) : Chose(), c(c) {
	addEntropy(c);
}

void TerrainQuadHerbe::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,1000)); // TODO
}

void TerrainQuadHerbe::triangulation() {
	triangles.reserve(2);
	addGPUTriangle(new GPUTriangle(c[NE], c[NW], c[SW], 0x11, 0xaa, 0x22));
	addGPUTriangle(new GPUTriangle(c[SW], c[SE], c[NE], 0x11, 0xaa, 0x22));
}
