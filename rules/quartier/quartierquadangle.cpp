#include "all_includes.hh"

QuartierQuadAngle::QuartierQuadAngle(Quad _c) : QuartierQuad(_c) {
}

bool QuartierQuadAngle::split() {
	for (int i = 0; i < 4; i++) {
		if (Triangle(c[NW+i], c[NE+i], c[SE+i]).angle() >= Angle::d2r(130)) {
			addChild(QuartierTri::factory(seed, 0, Triangle(c[NE+i], c[SE+i], c[SW+i])));
			addChild(QuartierTri::factory(seed, 1, Triangle(c[SW+i], c[NW+i], c[NE+i])));
			return true;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (Triangle(c[NW+i], c[NE+i], c[SE+i]).angle() <= Angle::d2r(50)) {
			// "couper ce coin".
			Vertex n = Segment(c[NW+i], c[NE+i]).randomPos(seed, 0, 0.4f, 0.6f);
			Vertex e = Segment(c[NE+i], c[SE+i]).randomPos(seed, 1, 0.4f, 0.6f);
			Triangle tn = Triangle(n, c[NE+i], c[SE+i]);
			Triangle te = Triangle(c[NW+i], c[NE+i], e);
			if (tn.minAngle() > te.minAngle()) {
				addChild(QuartierTri::factory(seed, 0, tn));
				addChild(QuartierQuad::factory(seed, 1, Quad(n, c[SE+i], c[SW+i], c[NW+i])));
			} else {
				addChild(QuartierTri::factory(seed, 0, te));
				addChild(QuartierQuad::factory(seed, 1, Quad(c[NW+i], e, c[SE+i], c[SW+i])));
			}
			return true;
		}
	}
	// Ne devait jamais arriver ici !
	addChild(new BatimentQuad(c));
	return true;
}
