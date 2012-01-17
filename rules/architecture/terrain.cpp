#include "all_includes.hh"

TerrainQuad::TerrainQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void TerrainQuad::getBoundingBoxPoints() {
	addBBPoints(c);
}

void TerrainQuad::triangulation() {
	addGPUQuad(c, Couleurs::herbe);
}

TerrainTri::TerrainTri(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

void TerrainTri::getBoundingBoxPoints() {
	addBBPoints(c);
}

void TerrainTri::triangulation() {
	addGPUTriangle(c, Couleurs::herbe);
}
