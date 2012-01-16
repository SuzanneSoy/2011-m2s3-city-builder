#include "all_includes.hh"

BatimentQuadMur::BatimentQuadMur(Quad _c, Quad _ch) : Chose(), c(_c), ch(_ch) {
	addEntropy(c);
	addEntropy(ch);
	this->window = false;
}

void BatimentQuadMur::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(ch);
}

void BatimentQuadMur::setWindow(bool val) {
    val = val;
    this->window = val;
    Quad q = Quad(ch[NE],c[NE],c[NW],ch[NW]);
    int lr = (q.length(S) - 120)/2;

    Quad wFront = q.insetNESW(40,lr,120,lr);
    Quad wBack = wFront.offsetNormal(28);
    windowPos = Quad(wFront[SE],wBack[SE],wBack[SW],wFront[SW]);
    windowPosh = Quad(wFront[NE],wBack[NE],wBack[NW],wFront[NW]);
}

bool BatimentQuadMur::split() {
    if(!window)
        return false;

    Quad right = Quad(windowPos[NW],windowPos[SW],c[SW],c[NW]);
    Quad righth = Quad(windowPosh[NW],windowPosh[SW],ch[SW],ch[NW]);
    Quad left = Quad(c[NE],c[SE],windowPos[SE],windowPos[NE]);
    Quad lefth = Quad(ch[NE],ch[SE],windowPosh[SE],windowPosh[NE]);
    Quad top = Quad(windowPosh[NE],windowPosh[NW],windowPosh[SW],windowPosh[SE]);

    addChild(new BatimentQuadMur(c,windowPos));
    addChild(new BatimentQuadMur(windowPosh,ch));
    addChild(new BatimentQuadMur(left,lefth));
    addChild(new BatimentQuadMur(right,righth));

    return true;
}

void BatimentQuadMur::triangulation() {
    if(!window)
        addGPUOcto(c, ch, Couleurs::mur);
    //else
        //addGPUOcto(c, ch, 0xFF,0x10,0x00);
        //addGPUQuad(windowPosh,0xFF,0xFF,0x00);
}
