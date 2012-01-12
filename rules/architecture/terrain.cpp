#include "all_includes.hh"

TerrainQuad::TerrainQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void TerrainQuad::getBoundingBoxPoints() {
	// TODO : quelle hauteur mettre pour le terrain plat ? Il faut mettre 0 et ajuster le
	// calcul des splitBox et mergeBox pour prendre en compre la somme des surfaces
	// potentiellement visibles de l'objet.
	addBBPoints(c, 1000);
}

void TerrainQuad::triangulation() {
	addGPUQuad(c, 0x11, 0xaa, 0x22);
}

TerrainTri::TerrainTri(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

void TerrainTri::getBoundingBoxPoints() {
	// TODO : quelle hauteur mettre pour le terrain plat ? Il faut mettre 0 et ajuster le
	// calcul des splitBox et mergeBox pour prendre en compre la somme des surfaces
	// potentiellement visibles de l'objet.
	addBBPoints(c, 1000);
}

void TerrainTri::triangulation() {
	addGPUTriangle(c, 0x11, 0xaa, 0x22);
}
