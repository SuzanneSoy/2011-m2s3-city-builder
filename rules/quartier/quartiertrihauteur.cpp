#include "all_includes.hh"

QuartierTriHauteur::QuartierTriHauteur(Triangle c) : QuartierTri(c) {
}

bool QuartierTriHauteur::split() {
	// TODO : sélectionner le sommet avec l'angle le plus grand.
	// Triangle::cutCornerSideResult r = c.cutCornerSide(TOP, random(seed,0,0.33, 0.67);
	// addChild(new RouteQuadChaussee(r.cut));
	// addChild(new RouteTriChaussee(r.cutFrom));
	// addChild(QuartierTri::factory(seed, 1, r.left);
	// addChild(QuartierTri::factory(seed, 1, r.right);
	Vertex baseCenter = Segment(c[LEFT], c[RIGHT]).randomPos(seed, 0, 33, 67);

	Triangle tl(c[TOP], baseCenter, c[LEFT]);
	Triangle tr(c[RIGHT], baseCenter, c[TOP]);
	tl = tl.inset(LEFTSIDE, hrw);
	tr = tr.inset(RIGHTSIDE, hrw);

	addChild(new RouteQuadChaussee(Quad(tr[RIGHT], tr[TOP], tl[TOP], tl[LEFT])));
	addChild(new RouteTriChaussee(Triangle(tl[LEFT], c[TOP], tr[RIGHT])));
	addChild(QuartierTri::factory(seed, 1, tl));
	addChild(QuartierTri::factory(seed, 2, tr));
	return true;
}
