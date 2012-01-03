#include "all_includes.hh"

QuartierQuadAngle::QuartierQuadAngle(Vertex ne, Vertex se, Vertex sw, Vertex nw) : QuartierQuad(ne, se, sw, nw) {
}

QuartierQuadAngle::~QuartierQuadAngle() {
    children.clear();
    triangles.clear();
}

bool QuartierQuadAngle::split() {
	for (int i = 0; i < 4; i++) {
		if (Triangle(c[NW+i], c[NE+i], c[SE+i]).angle() >= Angle::d2r(130)) {
			Triangle t1(c[NE+i], c[SE+i], c[SW+i]);
			t1.offsetBase(-hrw);
			Triangle t2(c[SW+i], c[NW+i], c[NE+i]);
			t2.offsetBase(-hrw);
			addChild(QuartierTri::factory(seed, 0, t1.c[0], t1.c[1], t1.c[2]));
			addChild(QuartierTri::factory(seed, 1, t2.c[0], t2.c[1], t2.c[2]));
			addChild(new RouteQuadChaussee(t1.c[0], t1.c[2], t2.c[0], t2.c[2]));
			addChild(new RouteTriChaussee(t1.c[0], c[NE+i], t2.c[2]));
			addChild(new RouteTriChaussee(t2.c[0], c[SW+i], t1.c[2]));
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
				Vertex oldtnc2 = tn.c[2];
				tn.offsetBase(-hrw);
				q.offset(E, -hrw);
				addChild(QuartierTri::factory(seed, 0, tn.c[0], tn.c[1], tn.c[2]));
				addChild(QuartierQuad::factory(seed, 1, q.c[0], q.c[1], q.c[2], q.c[3]));
				addChild(new RouteQuadChaussee(tn.c[0], tn.c[2], q.c[1], q.c[0]));
				addChild(new RouteTriChaussee(q.c[1], oldtnc2, tn.c[2]));
			} else {
				q = Quad(c[NW+i], e, c[SE+i], c[SW+i]);
				Vertex oldtec0 = te.c[0];
				te.offsetBase(-hrw);
				q.offset(E, -hrw);
				addChild(QuartierTri::factory(seed, 0, te.c[0], te.c[1], te.c[2]));
				addChild(QuartierQuad::factory(seed, 1, q.c[0], q.c[1], q.c[2], q.c[3]));
				addChild(new RouteQuadChaussee(te.c[0], te.c[2], q.c[1], q.c[0]));
				addChild(new RouteTriChaussee(te.c[0], oldtec0, q.c[0]));
			}
			return true;
		}
	}
	// Ne devait jamais arriver ici !
	addChild(new TerrainQuadHerbe(c[NE], c[SE], c[SW], c[NW]));
	return true;
}
