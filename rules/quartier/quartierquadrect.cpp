#include "all_includes.hh"

QuartierQuadRect::QuartierQuadRect(Vertex ne, Vertex se, Vertex sw, Vertex nw) : QuartierQuad(ne, se, sw, nw) {
}

std::vector<Vertex*> QuartierQuadRect::getBoundingBoxPoints() const {
    std::vector<Vertex*> list;
    return list;
}

bool QuartierQuadRect::subdivide() {
	Vertex n = Segment(corner[NW], corner[NE]).randomPos(seed, 0, 33, 67);
	Vertex s = Segment(corner[SE], corner[SW]).randomPos(seed, 1, 33, 67);

	Quad qe = Quad(corner[NE], corner[SE], s, n);
	Quad qw = Quad(corner[SW], corner[NW], n, s);
	qe.offset(W,-hrw);
	qw.offset(W,-hrw);

	addChild(new RouteQuadChaussee(qe.corner[NW], qe.corner[SW], qw.corner[NW], qw.corner[SW]));
	addChild(QuartierQuad::factory(seed, 2, qe.corner[0], qe.corner[1], qe.corner[2], qe.corner[3]));
	addChild(QuartierQuad::factory(seed, 3, qw.corner[0], qw.corner[1], qw.corner[2], qw.corner[3]));
	return true;
}
