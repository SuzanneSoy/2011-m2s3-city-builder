#include "all_includes.hh"

QuartierTriTrapeze::QuartierTriTrapeze(Triangle c) : QuartierTri(c) {
}

bool QuartierTriTrapeze::split() {
	// TODO : sélectionner le sommet avec l'angle le plus petit.
	Vertex left = Segment(c[LEFT], c[TOP]).randomPos(seed, 0, 33, 67);
	Vertex right = Segment(c[RIGHT], c[TOP]).randomPos(seed, 0, 33, 67);

	Triangle ttop(left, c[TOP], right);
	Quad trapeze(right, c[RIGHT], c[LEFT], left);
	ttop = ttop.inset(BASE, hrw);
	trapeze = trapeze.inset(N, hrw);

	addChild(new RouteQuadChaussee(Quad(ttop[RIGHT], trapeze[NE], trapeze[NW], ttop[LEFT])));
	addChild(QuartierTri::factory(seed, 1, ttop));
	addChild(QuartierQuad::factory(seed, 2, trapeze));
	return true;
}
