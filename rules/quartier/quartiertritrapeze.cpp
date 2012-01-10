#include "all_includes.hh"

QuartierTriTrapeze::QuartierTriTrapeze(Triangle _c) : QuartierTri(_c) {
}

bool QuartierTriTrapeze::split() {
	// TODO : sélectionner le sommet TOP avec l'angle le plus petit.
	Vertex left = Segment(c[LEFT], c[TOP]).randomPos(seed, 0, 1/3.f, 2/3.f);
	Vertex right = Segment(c[RIGHT], c[TOP]).randomPos(seed, 0, 1/3.f, 2/3.f);

	addChild(QuartierTri::factory(seed, 1, Triangle(left, c[TOP], right)));
	addChild(QuartierQuad::factory(seed, 2, Quad(right, c[RIGHT], c[LEFT], left)));
	return true;
}
