#include "all_includes.hh"

QuartierTriHauteur::QuartierTriHauteur(Vertex left, Vertex top, Vertex right) : QuartierTri(left, top, right) {
}

bool QuartierTriHauteur::split() {
	Vertex baseCenter = Segment(c[0], c[2]).randomPos(seed, 0, 33, 67);

	Triangle tl = Triangle(baseCenter, c[0], c[1]);
	Triangle tr = Triangle(c[1], c[2], baseCenter);
	tl.offsetBase(-hrw);
	tr.offsetBase(-hrw);

	addChild(new RouteQuadChaussee(tr.c[0], tr.c[2], tl.c[0], tl.c[2]));
	addChild(new RouteTriChaussee(tl.c[2], c[1], tr.c[0]));
	addChild(QuartierTri::factory(seed, 1, tl.c[2], tl.c[0], tl.c[1]));
	addChild(QuartierTri::factory(seed, 2, tr.c[1], tr.c[2], tr.c[0]));
	return true;
}
