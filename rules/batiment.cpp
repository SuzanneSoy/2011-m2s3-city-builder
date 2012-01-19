#include "all_includes.hh"

BatimentQuad_::BatimentQuad_(Quad _c, bool _isSub, QuadBool _w)
        : Chose(), c(_c), isSub(_isSub), w(_w) {
	addEntropy(c);
	for (int i = 0; i < 4; i++)
		addEntropy(w[N+i] ? 0 : 1);
}

bool BatimentQuad_::split() {
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

	return true;
}

void BatimentQuad_::bordureRouteTrottoir() {
	Quad qtrottoir = c.insetNESW(Dimensions::largeurRoute);
	Quad qinterieur = qtrottoir.insetNESW(Dimensions::largeurTrottoir);
	Quad qbatiments = qinterieur.offsetNormal(Dimensions::hauteurTrottoir);

	for (int i = 0; i < 4; i++) {
		addChild(new RouteQuad(Quad(c[NE+i],c[SE+i],qtrottoir[SE+i],qtrottoir[NE+i])));
		addChild(new TrottoirQuad(Quad(qtrottoir[NE+i],qtrottoir[SE+i],qinterieur[SE+i],qinterieur[NE+i])));
	}

	bool anglesAcceptable = c.minAngle() > Angle::d2r(90-60) && c.maxAngle() < Angle::d2r(90+60);

	if (anglesAcceptable && proba(seed, 0, 0.95f)) {
		addChild(new BatimentQuad_(qbatiments, true));
	} else {
		addChild(new TerrainQuad(qbatiments));
	}
}

void BatimentQuad_::sousBatiments() {
	Quad q = c << c.maxLengthSide();
	QuadBool qb = w << c.maxLengthSide();

	Vertex n = Segment(q[NW], q[NE]).randomPos(seed, 0, 1.f/3.f, 1.f/2.f);
	Vertex s = Segment(q[SE], q[SW]).randomPos(seed, 1, 1.f/3.f, 1.f/2.f);

	bool small = q.surface() < 4 * Dimensions::minSurfaceSousBatiment;

	if (small && qb[E] && proba(seed, 2, 0.3f)) {
		addChild(new TerrainQuad(Quad(q[SE], s, n, q[NE])));
		addChild(new BatimentQuad_(Quad(q[NW], n, s, q[SW]), true, QuadBool(qb[W],qb[N],true,qb[S])));
	} else if (small && qb[W] && proba(seed, 2, 0.5f)) {
		addChild(new BatimentQuad_(Quad(q[SE], s, n, q[NE]), true, QuadBool(qb[E],qb[S],true,qb[N])));
		addChild(new TerrainQuad(Quad(q[NW], n, s, q[SW])));
	} else {
		addChild(new BatimentQuad_(Quad(q[SE], s, n, q[NE]), true, QuadBool(qb[E],qb[S],false,qb[N])));
		addChild(new BatimentQuad_(Quad(q[NW], n, s, q[SW]), true, QuadBool(qb[W],qb[N],false,qb[S])));
	}
}

void BatimentQuad_::etages() {
	// TODO : indiquer aux bâtiments où est-ce qu'ils peuvent faire des fenêtres.
	float randEtages = floatInRange(seed, 0, 0.f, 1.f);
	int nbEtages = 1 + (int)(randEtages * randEtages * (Dimensions::maxEtages - 1));
	Quad q = c; // c.insetNESW(30)
	Quad qh;
	for (int i = 0; i < nbEtages; i++) {
		qh = q.offsetNormal(floatInRange(seed, 1+i, Dimensions::hauteurEtage*0.9f, Dimensions::hauteurEtage*1.1f));
		if (i == 0 && w[N] && w[S]) {
			addChild(new ArcheQuad(q, Segment(qh[NE],q[NE]).length()));
		} else {
			addChild(new EtageQuad(q,qh));
		}
		q = qh;
	}
    addChild(new ToitQuad(qh, Dimensions::hauteurToit));
}

void BatimentQuad_::triangulation() {
	Quad ch = c.offsetNormal(Dimensions::hauteurEtage + Dimensions::hauteurToit);
	addGPUQuad(ch, Couleurs::toit);
	for (int i = 0; i < 4; i++)
		addGPUQuad(Quad(c[NE+i], c[SE+i], ch[SE+i], ch[NE+i]), Couleurs::mur);
}

void BatimentQuad_::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurEtage + Dimensions::hauteurToit);
}

BatimentTri_::BatimentTri_(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

bool BatimentTri_::split() {
	return false;
}

void BatimentTri_::triangulation() {
	Triangle th = c.offsetNormal(Dimensions::hauteurEtage + Dimensions::hauteurToit);
	addGPUTriangle(th, Couleurs::toit);
	for (int i = 0; i < 3; i++)
		addGPUQuad(Quad(c[LEFT+i], c[TOP+i], th[TOP+i], th[LEFT+i]), Couleurs::mur);
}

void BatimentTri_::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurEtage + Dimensions::hauteurToit);
}
