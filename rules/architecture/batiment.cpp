#include "all_includes.hh"

BatimentQuad_::BatimentQuad_(Quad _c, bool _isSub, QuadBool _w)
        : Chose(), c(_c), isSub(_isSub), w(_w) {
	addEntropy(c);
	for (int i = 0; i < 4; i++)
		addEntropy(w[N+i] ? 0 : 1);
}

bool BatimentQuad_::split() {
	int minSurface = 100 * 100 * 100;
	Quad q = c << c.maxLengthSide();
	QuadBool qb = w << c.maxLengthSide();

	if (qb[N] || qb[E] || qb[S] || qb[W]) {
		if (q.surface() > 2 * minSurface) {
			Vertex n = Segment(q[NW], q[NE]).randomPos(seed, 0, 1.f/3.f, 1.f/2.f);
			Vertex s = Segment(q[SE], q[SW]).randomPos(seed, 1, 1.f/3.f, 1.f/2.f);

			addChild(new BatimentQuad_(Quad(q[SE], s, n, q[NE]), true, QuadBool(qb[E],qb[S],false,qb[N])));
			addChild(new BatimentQuad_(Quad(q[NW], n, s, q[SW]), true, QuadBool(qb[W],qb[N],false,qb[S])));
		} else {
			float randEtages = floatInRange(seed, 2, 0.f, 1.f);
			int maxEtages = 5;
			int nbEtages = 1 + (int)(randEtages * randEtages * (maxEtages - 1));
			Quad q = c;
			//ch = ch.insetNESW(30);
			Quad qh;
			for (int i = 0; i < nbEtages; i++) {
				qh = q.offsetNormal(floatInRange(seed, 3+i, Dimensions::hauteurEtage*0.9f, Dimensions::hauteurEtage*1.1f));
				addChild(new EtageQuad(q,qh));
				q = qh;
			}
            addChild(new ToitQuad(qh, Dimensions::hauteurToit));
		}
	} else {
		addChild(new TerrainQuad(c));
	}

	return true;
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
