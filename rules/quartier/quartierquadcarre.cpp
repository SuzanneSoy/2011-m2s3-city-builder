#include "all_includes.hh"

QuartierQuadCarre::QuartierQuadCarre(Vertex ne, Vertex se, Vertex sw, Vertex nw) : QuartierQuad(ne, se, sw, nw) {
}

QuartierQuadCarre::~QuartierQuadCarre() {
    children.clear();
    triangles.clear();
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
		q[i].offset(W,-hrw); q[i].offset(S,-hrw);
	}
	addChild(new RouteQuadCarrefour(q[0].c[SW], q[1].c[SW], q[2].c[SW], q[3].c[SW]));
	for (int i = 0; i < 4; i++) {
		addChild(new RouteQuadChaussee(q[NE+i].c[NW], q[NE+i].c[SW], q[NW+i].c[SW], q[NW+i].c[SE]));
		addChild(QuartierQuad::factory(seed, 4+i, q[i].c[0], q[i].c[1], q[i].c[2], q[i].c[3]));
	}
	return true;
}
