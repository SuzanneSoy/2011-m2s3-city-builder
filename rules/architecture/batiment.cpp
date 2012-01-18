#include "all_includes.hh"

BatimentQuad_::BatimentQuad_(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

bool BatimentQuad_::split() {
    Quad q;

    if(!isSub)
        q = c >> ((c.maxLengthNS() < c.maxLengthEW()) ? 1 : 0);
    else
        q = c;

    int minSurface = 1000000;

    if(q.surface() > 2* minSurface) {
        Vertex c1 = q[NW] + Vertex(q[NE] - q[NW])/2;
        Vertex c2 = q[SW] + Vertex(q[SE] - q[SW])/2;
        Quad q1 = Quad(c1,c2,q[SW],q[NW]).inset(E,30);
        Quad q2 = Quad(q[NE],q[SE],c2,c1).inset(W,30);

        addChild((new BatimentQuad_(q1))->isSubdivision(true));
        addChild((new BatimentQuad_(q2))->isSubdivision(true));
    }
    else {
        Quad ch = c.offsetNormal(Dimensions::hauteurEtage);
        addChild(new ToitQuad(ch, Dimensions::hauteurToit));
    }

	return true;
}

BatimentQuad_* BatimentQuad_::isSubdivision(bool val) {
    this->isSub  = val;
    return this;
}

void BatimentQuad_::triangulation() {
	Quad ch = c.offsetNormal(Dimensions::hauteurEtage + Dimensions::hauteurToit);
	addGPUQuad(ch, Couleurs::toit);
	for (int i = 0; i < 4; i++)
		addGPUQuad(Quad(c[NE+i], c[SE+i], ch[SE+i], ch[NE+i]), Couleurs::mur);
}

void BatimentQuad_::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurEtage + Dimensions::hauteurToit);
}

BatimentTri_::BatimentTri_(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

bool BatimentTri_::split() {
	return false;
}

void BatimentTri_::triangulation() {
	Triangle th = c.offsetNormal(Dimensions::hauteurEtage + Dimensions::hauteurToit);
	addGPUTriangle(th, Couleurs::toit);
	for (int i = 0; i < 3; i++)
		addGPUQuad(Quad(c[LEFT+i], c[TOP+i], th[TOP+i], th[LEFT+i]), Couleurs::mur);
}

void BatimentTri_::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurEtage + Dimensions::hauteurToit);
}
