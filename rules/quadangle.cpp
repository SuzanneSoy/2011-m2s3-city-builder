#include "all_includes.hh"

QuadAngle::QuadAngle(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Quadrilatere(ne, se, sw, nw) {
	triangulation();
}

bool QuadAngle::subdivide() {
	for (int i = 0; i < 4; i++) {
		if (Triangle(corner[NW+i], corner[NE+i], corner[SE+i]).angle() >= Angle::d2r(130)) {
			Triangle t1(corner[NE+i], corner[SE+i], corner[SW+i]);
			t1.offsetBase(-hrw);
			Triangle t2(corner[SW+i], corner[NW+i], corner[NE+i]);
			t2.offsetBase(-hrw);
			addChild(TileTri::factory(seed, 0, t1.v1, t1.v2, t1.v3));
			addChild(TileTri::factory(seed, 1, t2.v1, t2.v2, t2.v3));
			addChild(new Route(t1.v1, t1.v3, t2.v1, t2.v3));
			return true;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (Triangle(corner[NW+i], corner[NE+i], corner[SE+i]).angle() <= Angle::d2r(50)) {
			// "couper ce coin".
			Vertex n = (corner[NW+i] + corner[NE+i]) / 2;
			Vertex e = (corner[NE+i] + corner[SE+i]) / 2;
			Triangle tn = Triangle(n, corner[NE+i], corner[SE+i]);
			Triangle te = Triangle(corner[NW+i], corner[NE+i], e);
			Triangle t;
			Quad q;
			if (tn.minAngle() > te.minAngle()) {
				t = tn;
				q = Quad(n, corner[SE+i], corner[SW+i], corner[NW+i]);
			} else {
				t = te;
				q = Quad(corner[NW+i], e, corner[SE+i], corner[SW+i]);
			}
			t.offsetBase(-hrw);
			addChild(TileTri::factory(seed, 0, t.v1, t.v2, t.v3));
			q.offset(E, -hrw);
			addChild(Quadrilatere::factory(seed, 1, q.corner[0], q.corner[1], q.corner[2], q.corner[3]));
			addChild(new Route(t.v1, t.v3, q.corner[1], q.corner[0]));
			return true;
		}
	}
	// Ne devait jamais arriver ici !
	addChild(new QuadHerbe(corner[NE], corner[SE], corner[SW], corner[NW]));
	return true;
}
