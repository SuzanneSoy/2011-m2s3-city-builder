#include "all_includes.hh"

QuartierQuadAngle::QuartierQuadAngle(Quad c) : QuartierQuad(c) {
}

bool QuartierQuadAngle::split() {
	for (int i = 0; i < 4; i++) {
		if (Triangle(c[NW+i], c[NE+i], c[SE+i]).angle() >= Angle::d2r(130)) {
			// TODO : maintenant que Triangle::offset prend un paramètre side, on peut simplifier ce bazaar.
			Triangle t1 = Triangle(c[NE+i], c[SE+i], c[SW+i]).inset(BASE, hrw);
			Triangle t2 = Triangle(c[SW+i], c[NW+i], c[NE+i]).inset(BASE, hrw);
			addChild(QuartierTri::factory(seed, 0, t1));
			addChild(QuartierTri::factory(seed, 1, t2));
			addChild(new RouteQuadChaussee(Quad(t1[LEFT], t1[RIGHT], t2[LEFT], t2[RIGHT])));
			addChild(new RouteTriChaussee(Triangle(t2[RIGHT], c[NE+i], t1[LEFT])));
			addChild(new RouteTriChaussee(Triangle(t1[RIGHT], c[SW+i], t2[LEFT])));
			return true;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (Triangle(c[NW+i], c[NE+i], c[SE+i]).angle() <= Angle::d2r(50)) {
			// "couper ce coin".
			Vertex n = Segment(c[NW+i], c[NE+i]).randomPos(seed, 0, 0.4f, 0.6f);
			Vertex e = Segment(c[NE+i], c[SE+i]).randomPos(seed, 1, 0.4f, 0.6f);
			Triangle tn = Triangle(n, c[NE+i], c[SE+i]);
			Triangle te = Triangle(c[NW+i], c[NE+i], e);
			Quad q;
			if (tn.minAngle() > te.minAngle()) {
				q = Quad(n, c[SE+i], c[SW+i], c[NW+i]).inset(E, hrw);
				Vertex oldtnright = tn[RIGHT];
				tn = tn.inset(BASE, hrw);
				addChild(QuartierTri::factory(seed, 0, tn));
				addChild(QuartierQuad::factory(seed, 1, q));
				addChild(new RouteQuadChaussee(Quad(tn[LEFT], tn[RIGHT], q[SE], q[NE])));
				addChild(new RouteTriChaussee(Triangle(tn[RIGHT], oldtnright, q[SE])));
			} else {
				q = Quad(c[NW+i], e, c[SE+i], c[SW+i]).inset(E, hrw);
				Vertex oldteleft = te[LEFT];
				te = te.inset(BASE, hrw);
				addChild(QuartierTri::factory(seed, 0, te));
				addChild(QuartierQuad::factory(seed, 1, q));
				addChild(new RouteQuadChaussee(Quad(te[LEFT], te[RIGHT], q[SE], q[NE])));
				addChild(new RouteTriChaussee(Triangle(q[NE], oldteleft, te[LEFT])));
			}
			return true;
		}
	}
	// Ne devait jamais arriver ici !
	addChild(new TerrainQuadHerbe(c));
	return true;
}
