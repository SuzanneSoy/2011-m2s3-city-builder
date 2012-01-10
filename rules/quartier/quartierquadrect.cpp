#include "all_includes.hh"

QuartierQuadRect::QuartierQuadRect(Quad _c) : QuartierQuad(_c) {
}

bool QuartierQuadRect::split() {
	Vertex n = Segment(c[NW], c[NE]).randomPos(seed, 0, 1/3.f, 2/3.f);
	Vertex s = Segment(c[SE], c[SW]).randomPos(seed, 1, 1/3.f, 2/3.f);

	addChild(QuartierQuad::factory(seed, 2, Quad(c[NE], c[SE], s, n)));
	addChild(QuartierQuad::factory(seed, 3, Quad(c[SW], c[NW], n, s)));
	return true;
}
