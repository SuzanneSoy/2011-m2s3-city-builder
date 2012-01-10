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
    this->window = val;
    Quad q = Quad(ch[SE],c[SE],c[SW],ch[SW]);
    int lr = (q.length(S) - 100)/40;
    std::cout << q.inset(E,60).surface() << std::endl;
    Quad wFront = q.inset(N,40).inset(S,100).inset(E,lr).inset(W,lr);
    Quad wBack = wFront.offsetNormal(28);
    windowPos = Quad(wBack[SE],wFront[SE],wFront[SW],wBack[SW]);
    windowPosh = Quad(wBack[NE],wFront[NE],wFront[NW],wBack[NW]);

    //std::cout << "lr" << lr << std::endl;
    //std::cout << wFront[NE] << std::endl;
    //std::cout << q[SE] << std::endl;
    //std::cout << q[SW] << std::endl;
    //std::cout << q[NW] << std::endl << std::endl;
}

bool BatimentQuadMur::split() {
    if(!window)
        return false;

    Quad left = c;
    Quad right = c;
    Quad top = c;
    Quad bottom = c;


    addChild(new BatimentQuadMur(c,windowPos));
    addChild(new BatimentQuadMur(windowPosh,ch));

    return true;
}

void BatimentQuadMur::triangulation() {
    if(!window)
        addGPUOcto(c, ch, 0xf1,0xe3,0xad);
    else
        addGPUOcto(c, ch, 0xFF,0x10,0x00);
}
