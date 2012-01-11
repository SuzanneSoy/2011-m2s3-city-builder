#include "all_includes.hh"

QuartierQuadCarre::QuartierQuadCarre(Quad _c) : QuartierQuad(_c) {
}

bool QuartierQuadCarre::split() {
	Vertex middle[4];
	Vertex center = c.insetNESW(c.minLength() / 4.f).randomPoint(seed, -1);

	for (int i = 0; i < 4; i++)
		middle[N+i] = Segment(c[NW+i], c[NE+i]).randomPos(seed, i, 0.25, 0.75);

	for (int i = 0; i < 4; i++)
		addChild(QuartierQuad::factory(seed, 4+i, Quad(c[NE+i], middle[E+i], center, middle[N+i])));

	return true;
}
