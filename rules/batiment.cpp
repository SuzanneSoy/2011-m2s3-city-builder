#include "all_includes.hh"

BatimentQuad::BatimentQuad(Quad _c, bool _isSub, QuadBool _w)
        : Chose(), c(_c), isSub(_isSub), w(_w) {
	addEntropy(c);
	for (int i = 0; i < 4; i++)
		addEntropy(w[N+i] ? 0 : 1);
}

void BatimentQuad::split() {
	if (!isSub) {
		bordureRouteTrottoir();
	} else {
		if (w[N] || w[E] || w[S] || w[W]) {
			if (c.surface() > 2 * Dimensions::minSurfaceSousBatiment) {
				sousBatiments();
			} else {
				etages();
			}
		} else {
			addChild(new TerrainQuad(c));
		}
	}
}

void BatimentQuad::bordureRouteTrottoir() {
	Quad qinterieur = c.insetNESW(Dimensions::largeurRoute + Dimensions::largeurTrottoir);
	Quad qbatiments = qinterieur.offsetNormal(Dimensions::hauteurTrottoir);

	for (int i = 0; i < 4; i++) {
		addChild(new RouteTrottoirQuad(Quad(c[NE+i],c[SE+i],qinterieur[SE+i],qinterieur[NE+i])));
	}

	bool anglesAcceptable = c.minAngle() > Angle::d2r(90-60) && c.maxAngle() < Angle::d2r(90+60);

	if (anglesAcceptable && proba(seed, 0, 0.95f)) {
		addChild(new BatimentQuad(qbatiments, true));
	} else {
		addChild(new TerrainQuad(qbatiments));
	}
}

void BatimentQuad::sousBatiments() {
	Quad q = c << c.maxLengthSide();
	QuadBool qb = w << c.maxLengthSide();

	float posDelta = std::min(1.f/6.f, q.minLengthEW() / q.length(N) * 0.2f);
	Vertex n = Segment(q[NW], q[NE]).randomPos(seed, 0, 0.5f - posDelta, 0.5f + posDelta);
	Vertex s = Segment(q[SE], q[SW]).randomPos(seed, 1, 0.5f - posDelta, 0.5f + posDelta);

	bool small = q.surface() < 4 * Dimensions::minSurfaceSousBatiment;

	if (small && qb[E] && proba(seed, 2, 0.3f)) {
		addChild(new TerrainQuad(Quad(q[SE], s, n, q[NE])));
		addChild(new BatimentQuad(Quad(q[NW], n, s, q[SW]), true, QuadBool(qb[W],qb[N],true,qb[S])));
	} else if (small && qb[W] && proba(seed, 2, 0.5f)) {
		addChild(new BatimentQuad(Quad(q[SE], s, n, q[NE]), true, QuadBool(qb[E],qb[S],true,qb[N])));
		addChild(new TerrainQuad(Quad(q[NW], n, s, q[SW])));
	} else {
		addChild(new BatimentQuad(Quad(q[SE], s, n, q[NE]), true, QuadBool(qb[E],qb[S],false,qb[N])));
		addChild(new BatimentQuad(Quad(q[NW], n, s, q[SW]), true, QuadBool(qb[W],qb[N],false,qb[S])));
	}
}

void BatimentQuad::etages() {
	float randEtages = floatInRange(seed, 0, 0.f, 1.f);
	int nbEtages = 1 + (int)(randEtages * randEtages * (Dimensions::maxEtages - 1));
	Quad q = c; // c.insetNESW(30)
	Quad qh;
	for (int i = 0; i < nbEtages; i++) {
		qh = q.offsetNormal(floatInRange(seed, 1+i, Dimensions::hauteurEtage*0.9f, Dimensions::hauteurEtage*1.1f));
		addChild(new EtageQuad(q, qh, w, i, nbEtages));
		q = qh;
	}
    addChild(new ToitQuad(qh, Dimensions::hauteurToit));
}

void BatimentQuad::triangulation() {
	if (w[N] || w[E] || w[S] || w[W]) {
		Quad ch = c.offsetNormal(Dimensions::hauteurEtage * 2 + Dimensions::hauteurToit);
		addGPUQuad(ch, Couleurs::toit);
		for (int i = 0; i < 4; i++)
			addGPUQuad(Quad(c[NE+i], c[SE+i], ch[SE+i], ch[NE+i]), Couleurs::mur);
	} else {
		addGPUQuad(c, Couleurs::herbe);
	}
}

void BatimentQuad::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurEtage * 2 + Dimensions::hauteurToit);
}

BatimentTri::BatimentTri(Triangle _c, bool _isSub, TriBool _w)
        : Chose(), c(_c), isSub(_isSub), w(_w) {
	addEntropy(c);
	for (int i = 0; i < 3; i++)
		addEntropy(w[LEFTSIDE+i] ? 0 : 1);
}

void BatimentTri::split() {
	if (!isSub) {
		bordureRouteTrottoir();
	} else {
		if (w[LEFTSIDE] || w[RIGHTSIDE] || w[BASE]) {
			if (c.surface() > 2 * Dimensions::minSurfaceSousBatiment) {
				sousBatiments();
			} else {
				etages();
			}
		} else {
			addChild(new TerrainTri(c));
		}
	}
}

void BatimentTri::triangulation() {
	Triangle th = c.offsetNormal(Dimensions::hauteurEtage * 2 + Dimensions::hauteurToit);
	addGPUTriangle(th, Couleurs::toit);
	for (int i = 0; i < 3; i++)
		addGPUQuad(Quad(c[LEFT+i], c[TOP+i], th[TOP+i], th[LEFT+i]), Couleurs::mur);
}

void BatimentTri::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurEtage * 2 + Dimensions::hauteurToit);
}

void BatimentTri::bordureRouteTrottoir() {
	Triangle tinterieur = c.insetLTR(Dimensions::largeurRoute + Dimensions::largeurTrottoir);
	Triangle tbatiments = tinterieur.offsetNormal(Dimensions::hauteurTrottoir);

	for (int i = 0; i < 4; i++) {
		addChild(new RouteTrottoirQuad(Quad(c[LEFT+i],c[TOP+i],tinterieur[TOP+i],tinterieur[LEFT+i])));
	}

	bool anglesAcceptable = c.minAngle() > Angle::d2r(90-60) && c.maxAngle() < Angle::d2r(90+60);

	if (anglesAcceptable && proba(seed, 0, 0.95f)) {
		addChild(new BatimentTri(tbatiments, true));
	} else {
		addChild(new TerrainTri(tbatiments));
	}
}

void BatimentTri::sousBatiments() {
	Triangle t = c << c.minAngleCorner();
	TriBool tb = w << c.minAngleCorner();

	// TODO : ajuster pour que la distance c[LEFT] -- left et c[LEFT] -- base soit similaire.
	Vertex left = Segment(t[LEFT], t[TOP]).randomPos(seed, 0, 1.f/3.f, 2.f/3.f);
	float dLeft = Segment(t[LEFT], left).length();
	float posBase = dLeft / Segment(t[LEFT], t[RIGHT]).length();
	if (posBase < 0.3f) posBase = 0.2f;
	else if (posBase > 0.7f) posBase = 0.8f;
	Vertex base = Segment(t[RIGHT], t[LEFT]).randomPos(seed, 1, posBase - 0.1f, posBase + 0.1f);

	bool small = t.surface() < 4 * Dimensions::minSurfaceSousBatiment;

	if (small && (tb[LEFTSIDE] || tb[RIGHTSIDE]) && proba(seed, 2, 0.3f)) {
		addChild(new TerrainTri(Triangle(base, t[LEFT], left)));
		addChild(new BatimentQuad(Quad(base, left, t[TOP], t[RIGHT]), true, QuadBool(true, w[LEFTSIDE], w[RIGHTSIDE], w[BASE])));
	} else if (small && (tb[LEFTSIDE] || tb[RIGHTSIDE] || tb[BASE]) && proba(seed, 2, 0.3f)) {
		addChild(new BatimentTri(Triangle(base, t[LEFT], left), true, TriBool(w[BASE], w[LEFTSIDE], true)));
		addChild(new TerrainQuad(Quad(base, left, t[TOP], t[RIGHT])));
	} else {
		addChild(new BatimentTri(Triangle(base, t[LEFT], left), true, TriBool(w[BASE], w[LEFTSIDE], false)));
		addChild(new BatimentQuad(Quad(base, left, t[TOP], t[RIGHT]), true, QuadBool(false, w[LEFTSIDE], w[RIGHTSIDE], w[BASE])));
	}
}

void BatimentTri::etages() {
	float randEtages = floatInRange(seed, 0, 0.f, 1.f);
	int nbEtages = 1 + (int)(randEtages * randEtages * (Dimensions::maxEtages - 1));
	Triangle t = c; // c.insetNESW(30)
	Triangle th;
	for (int i = 0; i < nbEtages; i++) {
		th = t.offsetNormal(floatInRange(seed, 1+i, Dimensions::hauteurEtage*0.9f, Dimensions::hauteurEtage*1.1f));
		addChild(new EtageTri(t, th, w, i, nbEtages));
		t = th;
	}
    addChild(new ToitTri(th, Dimensions::hauteurToit));
}
