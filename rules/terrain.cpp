#include "all_includes.hh"

TerrainQuad::TerrainQuad(Quad _c, bool _addTrees) : Chose(), c(_c), addTrees(_addTrees) {
	addEntropy(c);
}

void TerrainQuad::split() {
	if (!addTrees) return;

	addChild(new TerrainQuad(c, false));

	Vertex p[10];
	int maxNArbres = std::min(10, (int)(c.surface() / (7.f*7.f*100.f*100.f)));
	int pi = 0;
	int nArbres = hash2(seed, -1) % (maxNArbres + 1);
	for (int essai = 0; essai < nArbres * 2 && pi < nArbres; essai++) {
		p[pi] = c.insetProportionnal(0.7f).randomPoint(seed, essai);
		bool success = true;
		for (int j = 0; j < pi; j++) {
			if (Segment(p[j], p[pi]).length() < 3 * 100) {
				success = false;
				break;
			}
		}
		if (success) pi++;
	}
	for (int i = 0; i < pi; i++) {
		addChild(new Arbre(p[i], c));
	}
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
