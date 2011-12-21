#include "all_includes.hh"

QuartierQuadAngle::QuartierQuadAngle(Vertex ne, Vertex se, Vertex sw, Vertex nw) : QuartierQuad(ne, se, sw, nw) {
}

QuartierQuadAngle::~QuartierQuadAngle() {
    children.clear();
    triangles.clear();
}

bool QuartierQuadAngle::split() {
	for (int i = 0; i < 4; i++) {
		if (Triangle(corner[NW+i], corner[NE+i], corner[SE+i]).angle() >= Angle::d2r(130)) {
			Triangle t1(corner[NE+i], corner[SE+i], corner[SW+i]);
			t1.offsetBase(-hrw);
			Triangle t2(corner[SW+i], corner[NW+i], corner[NE+i]);
			t2.offsetBase(-hrw);
			addChild(QuartierTri::factory(seed, 0, t1.v1, t1.v2, t1.v3));
			addChild(QuartierTri::factory(seed, 1, t2.v1, t2.v2, t2.v3));
			addChild(new RouteQuadChaussee(t1.v1, t1.v3, t2.v1, t2.v3));
			addChild(new QuartierTri(t2.v3, corner[NE+i], t1.v1)); // TODO : new RouteTri
			addChild(new QuartierTri(t1.v3, corner[SW+i], t2.v1)); // TODO : new RouteTri
			return true;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (Triangle(corner[NW+i], corner[NE+i], corner[SE+i]).angle() <= Angle::d2r(50)) {
			// "couper ce coin".
			Vertex n = Segment(corner[NW+i], corner[NE+i]).randomPos(seed, 0, 40, 60);
			Vertex e = Segment(corner[NE+i], corner[SE+i]).randomPos(seed, 1, 40, 60);
			Triangle tn = Triangle(n, corner[NE+i], corner[SE+i]);
			Triangle te = Triangle(corner[NW+i], corner[NE+i], e);
			Quad q;
			if (tn.minAngle() > te.minAngle()) {
				q = Quad(n, corner[SE+i], corner[SW+i], corner[NW+i]);
				Vertex oldv3 = tn.v3;
				tn.offsetBase(-hrw);
				q.offset(E, -hrw);
				addChild(QuartierTri::factory(seed, 0, tn.v1, tn.v2, tn.v3));
				addChild(QuartierQuad::factory(seed, 1, q.corner[0], q.corner[1], q.corner[2], q.corner[3]));
				addChild(new RouteQuadChaussee(tn.v1, tn.v3, q.corner[1], q.corner[0]));
				addChild(new QuartierTri(tn.v3, oldv3, q.corner[1])); // TODO : new RouteTri
			} else {
				q = Quad(corner[NW+i], e, corner[SE+i], corner[SW+i]);
				Vertex oldv1 = te.v1;
				te.offsetBase(-hrw);
				q.offset(E, -hrw);
				addChild(QuartierTri::factory(seed, 0, te.v1, te.v2, te.v3));
				addChild(QuartierQuad::factory(seed, 1, q.corner[0], q.corner[1], q.corner[2], q.corner[3]));
				addChild(new RouteQuadChaussee(te.v1, te.v3, q.corner[1], q.corner[0]));
				addChild(new QuartierTri(q.corner[0], oldv1, te.v1)); // TODO : new RouteTri
			}
			return true;
		}
	}
	// Ne devait jamais arriver ici !
	addChild(new TerrainQuadHerbe(corner[NE], corner[SE], corner[SW], corner[NW]));
	return true;
}
