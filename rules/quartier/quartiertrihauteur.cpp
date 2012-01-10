#include "all_includes.hh"

QuartierTriHauteur::QuartierTriHauteur(Triangle _c) : QuartierTri(_c) {
}

bool QuartierTriHauteur::split() {
	// TODO : sélectionner le sommet TOP avec l'angle le plus grand.
	Vertex baseCenter = Segment(c[LEFT], c[RIGHT]).randomPos(seed, 0, 1/3.f, 2/3.f);

	addChild(QuartierTri::factory(seed, 1, Triangle(c[TOP], baseCenter, c[LEFT])));
	addChild(QuartierTri::factory(seed, 2, Triangle(c[RIGHT], baseCenter, c[TOP])));
	return true;
}
