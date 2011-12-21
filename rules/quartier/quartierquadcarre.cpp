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

	Vertex cn = Segment(corner[NW], corner[NE]).randomPos(seed, -1, 25, 75);
	Vertex cs = Segment(corner[SE], corner[SW]).randomPos(seed, -2, 25, 75);
	Vertex c = Segment(cn, cs).randomPos(seed, -3, 25, 75);

	for (int i = 0; i < 4; i++) {
		middle[N+i] = Segment(corner[NW+i], corner[NE+i]).randomPos(seed, i, 25, 75);
	}
	for (int i = 0; i < 4; i++) {
		q[i] = Quad(corner[NE+i], middle[E+i], c, middle[N+i]);
		q[i].offset(W,-hrw); q[i].offset(S,-hrw);
	}
	addChild(new RouteQuadCarrefour(q[0].corner[SW], q[1].corner[SW], q[2].corner[SW], q[3].corner[SW]));
	for (int i = 0; i < 4; i++) {
		addChild(new RouteQuadChaussee(q[NE+i].corner[NW], q[NE+i].corner[SW], q[NW+i].corner[SW], q[NW+i].corner[SE]));
		addChild(QuartierQuad::factory(seed, 4+i, q[i].corner[0], q[i].corner[1], q[i].corner[2], q[i].corner[3]));
	}
	return true;
}
