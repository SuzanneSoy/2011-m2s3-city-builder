#include "all_includes.hh"

QuartierQuadCarre::QuartierQuadCarre(Quad _c) : QuartierQuad(_c) {
}

bool QuartierQuadCarre::split() {
	Vertex middle[4];

	Vertex centerN = Segment(c[NW], c[NE]).randomPos(seed, -1, 0.25, 0.75);
	Vertex centerS = Segment(c[SE], c[SW]).randomPos(seed, -2, 0.25, 0.75);
	Vertex center = Segment(centerN, centerS).randomPos(seed, -3, 0.25, 0.75);

	for (int i = 0; i < 4; i++)
		middle[N+i] = Segment(c[NW+i], c[NE+i]).randomPos(seed, i, 0.25, 0.75);

	for (int i = 0; i < 4; i++)
		addChild(QuartierQuad::factory(seed, 4+i, Quad(c[NE+i], middle[E+i], center, middle[N+i])));

	return true;
}
