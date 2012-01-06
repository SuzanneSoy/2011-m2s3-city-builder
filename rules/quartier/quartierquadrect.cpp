#include "all_includes.hh"

QuartierQuadRect::QuartierQuadRect(Quad c) : QuartierQuad(c) {
}

bool QuartierQuadRect::split() {
	Vertex n = Segment(c[NW], c[NE]).randomPos(seed, 0, 33, 67);
	Vertex s = Segment(c[SE], c[SW]).randomPos(seed, 1, 33, 67);

	Quad qe = Quad(c[NE], c[SE], s, n).inset(W,hrw);
	Quad qw = Quad(c[SW], c[NW], n, s).inset(W,hrw);

	addChild(new RouteQuadChaussee(Quad(qe[NW], qe[SW], qw[NW], qw[SW])));
	addChild(QuartierQuad::factory(seed, 2, qe));
	addChild(QuartierQuad::factory(seed, 3, qw));
	return true;
}
