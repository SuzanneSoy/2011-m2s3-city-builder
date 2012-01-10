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

    addChild(new BatimentQuadMur(me,meh));
    addChild(new BatimentQuadMur(mw,mwh));
    addChild(new BatimentQuadMur(mn,mnh));
    addChild(new BatimentQuadMur(ms,msh));
    return true;
}

void BatimentQuadBlock::triangulation() {
    addGPUOcto(c,ch, 0xF1, 0xE0, 0xE0);
}
