#include "all_includes.hh"

BatimentQuad_::BatimentQuad_(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

bool BatimentQuad_::split() {
	//addChild()
	return true;
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
