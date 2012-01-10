#include "all_includes.hh"

QuartierTriCentre::QuartierTriCentre(Triangle _c) : QuartierTri(_c) {
}

bool QuartierTriCentre::split() {
	// TODO : maxLength / 6 au lieu de 1000
	Vertex center = c.insetLTR(1000).randomPoint(seed, 0);
	Vertex edgePoint[3];
	for (int i = 0; i < 3; i++)
		edgePoint[LEFTSIDE+i] = Segment(c[LEFT+i], c[TOP+i]).randomPos(seed, i+1, 1/3.f, 2/3.f);

	for (int i = 0; i < 3; i++) {
		Quad q = Quad(c[TOP+i], edgePoint[RIGHTSIDE+i], center, edgePoint[LEFTSIDE+i]);
		addChild(QuartierQuad::factory(seed, i+4, q));
	}
	return true;
}
