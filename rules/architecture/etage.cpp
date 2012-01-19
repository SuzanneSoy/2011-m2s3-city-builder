#include "all_includes.hh"

EtageQuad::EtageQuad(Quad _c, Quad _ch, bool _we, bool _ws, bool _ww, bool _wn)
        : Chose(), c(_c), ch(_ch), we(_we), ws(_ws), ww(_ww), wn(_wn) {
	addEntropy(c);
	addEntropy(ch);
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

    MurQuad *mme = new MurQuad(me << 1,meh << 1,we);
    MurQuad *mmn = new MurQuad(mn,mnh,wn);
    MurQuad *mmw = new MurQuad(mw >> 1,mwh >> 1,ww);
    MurQuad *mms = new MurQuad(ms >> 2,msh >> 2,ws);
    addChild(mme);
    addChild(mmw);
    addChild(mmn);
    addChild(mms);
    return true;
}

void EtageQuad::triangulation() {
    addGPUOcto(c,ch, 0xF1E0E0);
}
