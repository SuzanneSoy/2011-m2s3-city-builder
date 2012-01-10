#include "all_includes.hh"

BatimentQuadBlock::BatimentQuadBlock(Quad _c, float _height) : Chose(), c(_c), height(_height) {
	addEntropy(c);
}

void BatimentQuadBlock::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height)); // TODO
}

bool BatimentQuadBlock::split() {
    Quad me = c;
    Quad ms = c;
    Quad mw = c;
    Quad mn = c;

    me[NW] = me[NE] + ((me[NW] - me[NE]) / me.length(N))*28;
    me[SW] = me[SE] + ((me[SW] - me[SE]) / me.length(S))*28;
    mw[NE] = mw[NW] + ((mw[NE] - mw[NW]) / mw.length(N))*28;
    mw[SE] = mw[SW] + ((mw[SE] - mw[SW]) / mw.length(S))*28;
    mn.inset(W,-28); mn.inset(E,-28);
    mn[SW] = mn[NW] + ((mn[SW] - mn[NW]) / mn.length(W))*28;
    mn[SE] = mn[NE] + ((mn[SE] - mn[NE]) / mn.length(E))*28;
    ms.inset(W,-28); ms.inset(E,-28);
    ms[NW] = ms[SW] + ((ms[NW] - ms[SW]) / ms.length(W))*28;
    ms[NE] = ms[SE] + ((ms[NE] - ms[SE]) / ms.length(E))*28;

    addChild(new BatimentQuadMur(me,height));
    addChild(new BatimentQuadMur(mw,height));
    addChild(new BatimentQuadMur(mn,height));
    addChild(new BatimentQuadMur(ms,height));
    return true;
}

void BatimentQuadBlock::triangulation() {
    addGPUOcto(c, c + Vertex(0,0,height), 0xF1, 0xE0, 0xE0);
}
