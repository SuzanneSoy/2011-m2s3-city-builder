#include "all_includes.hh"

QuartierQuadCarre::QuartierQuadCarre(Quad c) : QuartierQuad(c) {
}

bool QuartierQuadCarre::split() {
	Vertex middle[4];
	Quad q[4];

	Vertex centerN = Segment(c[NW], c[NE]).randomPos(seed, -1, 25, 75);
	Vertex centerS = Segment(c[SE], c[SW]).randomPos(seed, -2, 25, 75);
	Vertex center = Segment(centerN, centerS).randomPos(seed, -3, 25, 75);

	for (int i = 0; i < 4; i++) {
		middle[N+i] = Segment(c[NW+i], c[NE+i]).randomPos(seed, i, 25, 75);
	}
	for (int i = 0; i < 4; i++) {
		q[i] = Quad(c[NE+i], middle[E+i], center, middle[N+i]);
		q[i] = q[i].inset(W,hrw).inset(S,hrw);
	}
	addChild(new RouteQuadCarrefour(Quad(q[0][SW], q[1][SW], q[2][SW], q[3][SW])));
	for (int i = 0; i < 4; i++) {
		addChild(new RouteQuadChaussee(Quad(q[NE+i][NW], q[NE+i][SW], q[NW+i][SW], q[NW+i][SE])));
		addChild(QuartierQuad::factory(seed, 4+i, q[i]));
	}
	return true;
}
