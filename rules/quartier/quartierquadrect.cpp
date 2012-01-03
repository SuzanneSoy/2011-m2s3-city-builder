#include "all_includes.hh"

QuartierQuadRect::QuartierQuadRect(Vertex ne, Vertex se, Vertex sw, Vertex nw) : QuartierQuad(ne, se, sw, nw) {
}

QuartierQuadRect::~QuartierQuadRect() {
    children.clear();
    triangles.clear();
}

bool QuartierQuadRect::split() {
	Vertex n = Segment(c[NW], c[NE]).randomPos(seed, 0, 33, 67);
	Vertex s = Segment(c[SE], c[SW]).randomPos(seed, 1, 33, 67);

	Quad qe = Quad(c[NE], c[SE], s, n);
	Quad qw = Quad(c[SW], c[NW], n, s);
	qe.offset(W,-hrw);
	qw.offset(W,-hrw);

	addChild(new RouteQuadChaussee(qe.c[NW], qe.c[SW], qw.c[NW], qw.c[SW]));
	addChild(QuartierQuad::factory(seed, 2, qe.c[0], qe.c[1], qe.c[2], qe.c[3]));
	addChild(QuartierQuad::factory(seed, 3, qw.c[0], qw.c[1], qw.c[2], qw.c[3]));
	return true;
}
