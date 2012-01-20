#include "all_includes.hh"

MurQuad::MurQuad(Quad _c, Quad _ch, bool _window) : Chose(), c(_c), ch(_ch), window(_window) {
	addEntropy(c);
	addEntropy(ch);
	if(_window)
        setWindow();
}

void MurQuad::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(ch);
}

void MurQuad::setWindow() {
    Quad q = Quad(ch[NE],c[NE],c[NW],ch[NW]);
    float lr = (q.length(S) - 120)/2.f;

    Quad wFront = q.insetNESW(40,lr,120,lr);
    Quad wBack = wFront.offsetNormal(28);
    windowPos = Quad(wFront[SE],wBack[SE],wBack[SW],wFront[SW]);
    windowPosh = Quad(wFront[NE],wBack[NE],wBack[NW],wFront[NW]);
}

bool MurQuad::split() {
    if(!window)
        return false;

    float length = c.maxLengthNS();

    //if(length > 660) {
    if(false) {
        Quad qa = c.insetOpp(W,length/2);
        Quad qb = c.insetOpp(E,length-(length/2));
        Quad qah = ch.insetOpp(W,length/2);
        Quad qbh = ch.insetOpp(E,length-(length/2));

        addChild(new MurQuad(qa,qah,window));
        addChild(new MurQuad(qb,qbh,window));
    } else {
        Quad right = Quad(windowPos[NW],windowPos[SW],c[SW],c[NW]);
        Quad righth = Quad(windowPosh[NW],windowPosh[SW],ch[SW],ch[NW]);
        Quad left = Quad(c[NE],c[SE],windowPos[SE],windowPos[NE]);
        Quad lefth = Quad(ch[NE],ch[SE],windowPosh[SE],windowPosh[NE]);
        Quad top = Quad(windowPosh[NE],windowPosh[NW],windowPosh[SW],windowPosh[SE]);

        addChild(new MurQuad(c,windowPos,false));
        addChild(new MurQuad(windowPosh,ch, false));
        addChild(new MurQuad(left,lefth,false));
        addChild(new MurQuad(right,righth,false));
    }

    return true;
}

void MurQuad::triangulation() {
    addGPUFourQuads(c, ch, Couleurs::mur);
}

PlancherPlafond::PlancherPlafond(Quad _c, Type _type) : Chose(), c(_c), type(_type) {
	addEntropy(c);
	addEntropy((int)type);
}

void PlancherPlafond::triangulation() {
	unsigned int clr = Couleurs::plancher;
	if (type == PLAFOND)
		clr = Couleurs::plafond;
	addGPUQuad(c, clr);
}

void PlancherPlafond::getBoundingBoxPoints() {
	addBBPoints(c);
}
