#include "all_includes.hh"

QuartierQuadConcave::QuartierQuadConcave(Quad _c) : QuartierQuad(_c) {
}

bool QuartierQuadConcave::split() {
	for (int i = 0; i < 4; i++) {
		if (Triangle(c[NW+i], c[NE+i], c[SE+i]).angle() >= Angle::d2r(160)) {
			addChild(QuartierTri::factory(seed, 0, Triangle(c[NE+i], c[SE+i], c[SW+i])));
			addChild(QuartierTri::factory(seed, 1, Triangle(c[SW+i], c[NW+i], c[NE+i])));
			return true;
		}
	}
	throw "ERREUR : Ne devait jamais arriver ici !";
	return true;
}
