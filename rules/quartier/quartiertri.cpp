#include "all_includes.hh"

QuartierTri::QuartierTri(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

void QuartierTri::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,1000)); // TODO
}

Chose* QuartierTri::factory(int seed, int n, Triangle c) {
	bool small = c.minLength() < 3500;
	bool big = c.maxLength() >= 6000;
	bool verybig = c.minLength() >= 10000;
	bool anglesAcceptable = c.minAngle() > 30 && c.maxAngle() < 120;
	if (small) {
		return new RouteTrottoirTri(c);
	} else if (verybig && anglesAcceptable) {
		int choice = hash2(seed, n) % 3;
		if (choice == 0) {
			return new QuartierTriCentre(c);
		} else if (choice == 1) {
			return new QuartierTriHauteur(c);
		} else {
			return new QuartierTriTrapeze(c);
		}
	} else if (big && !small && c.maxAngle() < 60+15 && c.minAngle() > 60-15) {
		return new QuartierTriCentre(c);
	} else if (big && !small) {
		return new QuartierTriHauteur(c);
	} else if (big && !small) {
		return new QuartierTriTrapeze(c);
	} else {
		return new RouteTrottoirTri(c);
	}
}

bool QuartierTri::split() {
	return false;
}

void QuartierTri::triangulation() {
	triangles.reserve(1);
	addGPUTriangle(c, 0xf0, 0xc0, 0xc0);
}
