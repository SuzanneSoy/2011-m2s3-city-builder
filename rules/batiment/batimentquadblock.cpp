#include "all_includes.hh"

BatimentQuadBlock::BatimentQuadBlock(Quad _c, float _height) : Chose(), c(_c), height(_height) {
	addEntropy(c);
}

void BatimentQuadBlock::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

bool BatimentQuadBlock::split() {
    Quad me = c.insetOpp(E,28);
    Quad ms = c.inset(E,-28).inset(W,-28).insetOpp(S,28);
    Quad mw = c.insetOpp(W,28);
    Quad mn = c.inset(E,-28).inset(W,-28).insetOpp(N,28);

    addChild(new BatimentQuadMur(me,height));
    addChild(new BatimentQuadMur(mw,height));
    addChild(new BatimentQuadMur(mn,height));
    addChild(new BatimentQuadMur(ms,height));
    return true;
}

void BatimentQuadBlock::triangulation() {
    addGPUOcto(c, c + Vertex(0,0,height), 0xF1, 0xE0, 0xE0);
}
