#include "all_includes.hh"

QuartierQuadAngle::QuartierQuadAngle(Quad c) : QuartierQuad(c) {
}

bool QuartierQuadAngle::split() {
	for (int i = 0; i < 4; i++) {
		if (Triangle(c[NW+i], c[NE+i], c[SE+i]).angle() >= Angle::d2r(130)) {
			Triangle t1(c[NE+i], c[SE+i], c[SW+i]);
			t1.offsetBase(-hrw);
			Triangle t2(c[SW+i], c[NW+i], c[NE+i]);
			t2.offsetBase(-hrw);
			addChild(QuartierTri::factory(seed, 0, t1));
			addChild(QuartierTri::factory(seed, 1, t2));
			addChild(new RouteQuadChaussee(Quad(t1[LEFT], t1[RIGHT], t2[LEFT], t2[RIGHT])));
			addChild(new RouteTriChaussee(Triangle(t1[LEFT], c[NE+i], t2[RIGHT])));
			addChild(new RouteTriChaussee(Triangle(t2[LEFT], c[SW+i], t1[RIGHT])));
			return true;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (Triangle(c[NW+i], c[NE+i], c[SE+i]).angle() <= Angle::d2r(50)) {
			// "couper ce coin".
			Vertex n = Segment(c[NW+i], c[NE+i]).randomPos(seed, 0, 40, 60);
			Vertex e = Segment(c[NE+i], c[SE+i]).randomPos(seed, 1, 40, 60);
			Triangle tn = Triangle(n, c[NE+i], c[SE+i]);
			Triangle te = Triangle(c[NW+i], c[NE+i], e);
			Quad q;
			if (tn.minAngle() > te.minAngle()) {
				q = Quad(n, c[SE+i], c[SW+i], c[NW+i]);
				Vertex oldtnright = tn[RIGHT];
				tn.offsetBase(-hrw);
				q.offset(E, -hrw);
				addChild(QuartierTri::factory(seed, 0, tn));
				addChild(QuartierQuad::factory(seed, 1, q));
				addChild(new RouteQuadChaussee(Quad(tn[LEFT], tn[RIGHT], q[SE], q[NE])));
				addChild(new RouteTriChaussee(Triangle(q[SE], oldtnright, tn[RIGHT])));
			} else {
				q = Quad(c[NW+i], e, c[SE+i], c[SW+i]);
				Vertex oldteleft = te[LEFT];
				te.offsetBase(-hrw);
				q.offset(E, -hrw);
				addChild(QuartierTri::factory(seed, 0, te));
				addChild(QuartierQuad::factory(seed, 1, q));
				addChild(new RouteQuadChaussee(Quad(te[LEFT], te[RIGHT], q[SE], q[NE])));
				addChild(new RouteTriChaussee(Triangle(te[LEFT], oldteleft, q[NE])));
			}
			return true;
		}
	}
	// Ne devait jamais arriver ici !
	addChild(new TerrainQuadHerbe(c));
	return true;
}
