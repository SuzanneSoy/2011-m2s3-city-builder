#include "all_includes.hh"

BatimentQuadBlock::BatimentQuadBlock(Quad _c, Quad _ch) : Chose(), c(_c), ch(_ch) {
	addEntropy(c);
	addEntropy(ch);
}

void BatimentQuadBlock::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(ch);
}

bool BatimentQuadBlock::split() {
    Quad me = c.insetOpp(E,28);
    Quad ms = c.inset(E,28).inset(W,28).insetOpp(S,28);
    Quad mw = c.insetOpp(W,28);
    Quad mn = c.inset(E,28).inset(W,28).insetOpp(N,28);
    Quad meh = ch.insetOpp(E,28);
    Quad msh = ch.inset(E,28).inset(W,28).insetOpp(S,28);
    Quad mwh = ch.insetOpp(W,28);
    Quad mnh = ch.inset(E,28).inset(W,28).insetOpp(N,28);

    BatimentQuadMur *mme = new BatimentQuadMur(me,meh);
    BatimentQuadMur *mmn = new BatimentQuadMur(mn,mnh);
    BatimentQuadMur *mmw = new BatimentQuadMur(mw,mwh);
    BatimentQuadMur *mms = new BatimentQuadMur(ms,msh);
    mme->setWindow(true);
    //mmn->setWindow(true);
    mmw->setWindow(true);
    mms->setWindow(true);
    addChild(mme);
    addChild(mmw);
    addChild(mmn);
    addChild(mms);
    return true;
}

void BatimentQuadBlock::triangulation() {
    addGPUOcto(c,ch, 0xF1E0E0);
}
