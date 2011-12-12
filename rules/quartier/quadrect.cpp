#include "all_includes.hh"

QuadRect::QuadRect(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Quadrilatere(ne, se, sw, nw) {
}

bool QuadRect::subdivide() {
	Vertex n = Segment(corner[NW], corner[NE]).randomPos(seed, 0, 33, 67);
	Vertex s = Segment(corner[SE], corner[SW]).randomPos(seed, 1, 33, 67);

	Quad qe = Quad(corner[NE], corner[SE], s, n);
	Quad qw = Quad(corner[SW], corner[NW], n, s);
	qe.offset(W,-hrw);
	qw.offset(W,-hrw);

	addChild(new Route(qe.corner[NW], qe.corner[SW], qw.corner[NW], qw.corner[SW]));
	addChild(Quadrilatere::factory(seed, 2, qe.corner[0], qe.corner[1], qe.corner[2], qe.corner[3]));
	addChild(Quadrilatere::factory(seed, 3, qw.corner[0], qw.corner[1], qw.corner[2], qw.corner[3]));
	return true;
}
