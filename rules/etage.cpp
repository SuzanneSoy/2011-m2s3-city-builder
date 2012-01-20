#include "all_includes.hh"

EtageQuad::EtageQuad(Quad _c, Quad _ch, QuadBool _w, int _etage, int _nbEtages) : Chose(), c(_c), ch(_ch), w(_w), etage(_etage), nbEtages(_nbEtages) {
	addEntropy(c);
	addEntropy(ch);
	for (int i = 0; i < 4; i++)
		addEntropy(w[N+i] ? 0 : 1);
}

void EtageQuad::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(ch);
}

void EtageQuad::split() {
	if (nbEtages > 1 && etage == 0 && ((w[N] && w[S]) || (w[E] && w[W])) && c.minLengthEW() > 800 && proba(seed, 0, 0.8)) {
		Quad q = c << ((w[N] && w[S]) ? 0 : 1);
		Quad qh = ch << ((w[N] && w[S]) ? 0 : 1);
		Vertex n = (q[NW] + q[NE]) / 2.f;
		Vertex s = (q[SE] + q[SW]) / 2.f;
		Vertex nh = (qh[NW] + qh[NE]) / 2.f;
		Vertex sh = (qh[SE] + qh[SW]) / 2.f;
		Quad e = Quad(q[NE], q[SE], s, n).inset(W, 200);
		Quad w = Quad(n, s, q[SW], q[NW]).inset(E, 200);
		Quad eh = Quad(qh[NE], qh[SE], sh, nh).inset(W, 200);
		Quad wh = Quad(nh, sh, qh[SW], qh[NW]).inset(E, 200);
		Quad ei = e.insetNESW(28, 28, 28, 0);
		Quad wi = w.insetNESW(28, 0, 28, 28);
		Quad eih = eh.insetNESW(28, 28, 28, 0);
		Quad wih = wh.insetNESW(28, 0, 28, 28);
		// TODO : ArcheQuad(q, q);
		addChild(new ArcheQuad(Quad(e[NW], e[SW], w[SE], w[NE]), Segment(qh[NE], q[NE]).length()));
		// Mur sur e[N], e[E], e[S], w[S], w[W], w[N];
		for (int i = 0; i < 3; i++) {
			addChild(new MurQuad(Quad(e[NE+i], ei[NE+i], ei[NW+i], e[NW+i]), Quad(eh[NE+i], eih[NE+i], eih[NW+i], eh[NW+i])));
			addChild(new MurQuad(Quad(w[SE+i], w[SW+i], wi[SW+i], wi[SE+i]), Quad(wh[SE+i], wh[SW+i], wih[SW+i], wih[SE+i])));
		}
	} else {
		Quad me = c.insetOpp(E,28);
		Quad ms = c.inset(E,28).inset(W,28).insetOpp(S,28);
		Quad mw = c.insetOpp(W,28);
		Quad mn = c.inset(E,28).inset(W,28).insetOpp(N,28);
		Quad meh = ch.insetOpp(E,28);
		Quad msh = ch.inset(E,28).inset(W,28).insetOpp(S,28);
		Quad mwh = ch.insetOpp(W,28);
		Quad mnh = ch.inset(E,28).inset(W,28).insetOpp(N,28);

        QuadBool d = QuadBool(false,false,false,false);

        if(etage == 0) {
            if(w[E])        d[E] = true;
            else if(w[W])   d[W] = true;
            else if(w[N])   d[N] = true;
            else if(w[S])   d[S] = true;
        }

		addChild(new MurQuad(me << 1,meh << 1,w[E]^d[E],false,false,d[E]));
		addChild(new MurQuad(mw >> 1,mwh >> 1,w[W]^d[W],false,false,d[W]));
		addChild(new MurQuad(mn,mnh,w[N]^d[N],false,false,d[N]));
		addChild(new MurQuad(ms >> 2,msh >> 2,w[S]^d[S],false,false,d[S]));
	}
	addChild(new PlancherPlafond(c, PlancherPlafond::PLANCHER));
	addChild(new PlancherPlafond(ch.offsetNormal(-10), PlancherPlafond::PLAFOND));
}

void EtageQuad::triangulation() {
    addGPUFourQuads(c,ch, Couleurs::mur);
    addGPUQuad(ch.offsetNormal(-30), Couleurs::plafond);
    addGPUQuad(c, Couleurs::plancher);
}

EtageTri::EtageTri(Triangle _c, Triangle _ch, TriBool _w, int _etage, int _nbEtages) : Chose(), c(_c), ch(_ch), w(_w), etage(_etage), nbEtages(_nbEtages) {
	addEntropy(c);
	addEntropy(ch);
	for (int i = 0; i < 3; i++)
		addEntropy(w[LEFTSIDE+i] ? 0 : 1);
}

void EtageTri::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(ch);
}

void EtageTri::split() {
	Triangle small = c.insetLTR(28);
	Triangle smallh = ch.insetLTR(28);

	TriBool d(false,false,false);

	if(etage == 0) {
		if(w[LEFTSIDE])       d[LEFTSIDE] = true;
		else if(w[RIGHTSIDE]) d[RIGHTSIDE] = true;
		else if(w[BASE])      d[BASE] = true;
	}

	for (int i = 0; i < 3; i++) {
		Quad q = Quad(c[TOP+i], small[TOP+i], small[LEFT+i], c[LEFT+i]);
		Quad qh = Quad(ch[TOP+i], smallh[TOP+i], smallh[LEFT+i], ch[LEFT+i]);
		addChild(new MurQuad(q, qh, w[LEFTSIDE+i]^d[LEFTSIDE+i],false,false,d[LEFTSIDE+i]));
	}

	addChild(new PlancherPlafondTri(c, PlancherPlafondTri::PLANCHER));
	addChild(new PlancherPlafondTri(ch.offsetNormal(-10), PlancherPlafondTri::PLAFOND));
}

void EtageTri::triangulation() {
    addGPUThreeQuads(c,ch, Couleurs::mur);
    addGPUTriangle(ch.offsetNormal(-30), Couleurs::plafond);
    addGPUTriangle(c, Couleurs::plancher);
}
