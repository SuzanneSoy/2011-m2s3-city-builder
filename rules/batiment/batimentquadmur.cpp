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
    Quad q = Quad(ch[SE],c[SE],c[SW],ch[SW]);
    int lr = (q.length(S) - 100)/2;

    Quad wFront = q.insetNESW(40,lr,110,lr);
    Quad wBack = wFront.offsetNormal(280);
    windowPos = Quad(wFront[SE],wBack[SE],wBack[SW],wFront[SW]);
    windowPosh = Quad(wFront[NE],wBack[NE],wBack[NW],wFront[NW]);

    //addGPUQuad(wFront,0xFF,0xFF,0x00);
    //addGPUQuad(wBack,0xFF,0xFF,0x00);
    //addGPUQuad(windowPos,0x90,0x90,0xFF);
    //addGPUQuad(windowPosh,0x90,0x90,0xFF);

    //std::cout << "lr" << lr << std::endl;
    //std::cout << windowPos[NE] << std::endl;
    //std::cout << windowPos[SE] << std::endl;
    //std::cout << q[SW] << std::endl;
    //std::cout << q[NW] << std::endl << std::endl;
}

bool BatimentQuadMur::split() {
    if(!window)
        return false;

    Quad right = Quad(windowPos[NW],windowPos[SW],c[SW],c[NW]);
    Quad righth = Quad(windowPosh[NW],windowPosh[SW],ch[SW],ch[NW]);
    Quad left = Quad(c[NE],c[SE],windowPos[SE],windowPos[NE]);
    Quad lefth = Quad(ch[NE],ch[SE],windowPosh[SE],windowPosh[NE]);
    Quad top = Quad(windowPosh[NE],windowPosh[NW],windowPosh[SW],windowPosh[SE]);
//addGPUQuad(windowPosh[NE],top[NW],ch[NW],ch[NE],0xFF,0x90,0x90);
//addGPUQuad(ch,0x80,0x80,0xFF);
    addChild(new BatimentQuadMur(c,windowPos));
    addChild(new BatimentQuadMur(windowPosh,ch));
    addChild(new BatimentQuadMur(left,lefth));
    addChild(new BatimentQuadMur(right,righth));

    return true;
}

void BatimentQuadMur::triangulation() {
    if(!window)
        addGPUOcto(c, ch, 0xf1,0xe3,0xad);
    //else
        //addGPUOcto(c, ch, 0xFF,0x10,0x00);
        //addGPUQuad(windowPosh,0xFF,0xFF,0x00);
}
