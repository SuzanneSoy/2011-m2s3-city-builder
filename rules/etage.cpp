#include "all_includes.hh"

EtageQuad::EtageQuad(Quad _c, Quad _ch, QuadBool _w) : Chose(), c(_c), ch(_ch), w(_w) {
	addEntropy(c);
	addEntropy(ch);
	for (int i = 0; i < 4; i++)
		addEntropy(w[N+i] ? 0 : 1);
}

void EtageQuad::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(ch);
}

bool EtageQuad::split() {
    Quad me = c.insetOpp(E,28);
    Quad ms = c.inset(E,28).inset(W,28).insetOpp(S,28);
    Quad mw = c.insetOpp(W,28);
    Quad mn = c.inset(E,28).inset(W,28).insetOpp(N,28);
    Quad meh = ch.insetOpp(E,28);
    Quad msh = ch.inset(E,28).inset(W,28).insetOpp(S,28);
    Quad mwh = ch.insetOpp(W,28);
    Quad mnh = ch.inset(E,28).inset(W,28).insetOpp(N,28);

    addChild(new MurQuad(me << 1,meh << 1,w[E]));
    addChild(new MurQuad(mw >> 1,mwh >> 1,w[W]));
    addChild(new MurQuad(mn,mnh,w[N]));
    addChild(new MurQuad(ms >> 2,msh >> 2,w[S]));

    return true;
}

void EtageQuad::triangulation() {
    addGPUFourQuads(c,ch, Couleurs::mur);
    addGPUQuad(ch.offsetNormal(-30), Couleurs::plafond);
    addGPUQuad(c, Couleurs::plancher);
}
