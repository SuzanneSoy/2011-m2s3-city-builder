#include "all_includes.hh"

QuartierTri::QuartierTri(Triangle c) : Chose(), c(c) {
	addEntropy(c);
}

void QuartierTri::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,1000)); // TODO
}

Chose* QuartierTri::factory(int seed, int n, Triangle c) {
	bool small = c.minLength() < 2500;
	bool big = c.maxLength() >= 5000;
	if (small && !big) {
		return new BatimentTri(c);
	} else if (big) {
		int choice = hash2(seed, n) % 3;
		if (choice == 0) {
			// TODO : condition : générer seulement si les 3 angles sont proches de 60°
			return new QuartierTriCentre(c);
		} else if (choice == 1) {
			return new QuartierTriHauteur(c);
		} else {
			return new QuartierTriTrapeze(c);
		}
	} else {
		return new TerrainTriHerbe(c);
	}
}

bool QuartierTri::split() {
	return false;
}

void QuartierTri::triangulation() {
	triangles.reserve(1);
	addGPUTriangle(c, 0xf0, 0xc0, 0xc0);
}
