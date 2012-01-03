#include "all_includes.hh"

QuartierTriHauteur::QuartierTriHauteur(Vertex left, Vertex top, Vertex right) : QuartierTri(left, top, right) {
}

bool QuartierTriHauteur::split() {
	Vertex baseCenter = Segment(corner[0], corner[2]).randomPos(seed, 0, 33, 67);

	Triangle tl = Triangle(baseCenter, corner[0], corner[1]);
	Triangle tr = Triangle(corner[1], corner[2], baseCenter);
	tl.offsetBase(-hrw);
	tr.offsetBase(-hrw);

	addChild(new RouteQuadChaussee(tr.v1, tr.v3, tl.v1, tl.v3));
	addChild(new RouteTriChaussee(tl.v3, corner[1], tr.v1));
	addChild(QuartierTri::factory(seed, 1, tl.v3, tl.v1, tl.v2));
	addChild(QuartierTri::factory(seed, 2, tr.v2, tr.v3, tr.v1));
	return true;
}
