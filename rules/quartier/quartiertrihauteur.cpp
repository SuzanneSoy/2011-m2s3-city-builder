#include "all_includes.hh"

QuartierTriHauteur::QuartierTriHauteur(Triangle c) : QuartierTri(c) {
}

bool QuartierTriHauteur::split() {
	Vertex baseCenter = Segment(c[LEFT], c[RIGHT]).randomPos(seed, 0, 33, 67);

	Triangle tl = Triangle(baseCenter, c[LEFT], c[TOP]);
	Triangle tr = Triangle(c[TOP], c[RIGHT], baseCenter);
	tl.offsetBase(-hrw);
	tr.offsetBase(-hrw);

	addChild(new RouteQuadChaussee(Quad(tr[LEFT], tr[RIGHT], tl[LEFT], tl[RIGHT])));
	addChild(new RouteTriChaussee(Triangle(tl[RIGHT], c[TOP], tr[LEFT])));
	addChild(QuartierTri::factory(seed, 1, tl >> 1));
	addChild(QuartierTri::factory(seed, 2, tr << 1));
	return true;
}
