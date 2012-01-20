#include "all_includes.hh"

RouteTrottoirQuad::RouteTrottoirQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void RouteTrottoirQuad::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurTrottoir);
}

void RouteTrottoirQuad::triangulation() {
	Quad qtrottoir = c.inset(E, Dimensions::largeurRoute);
	Quad qtrottoirh = qtrottoir.offsetNormal(Dimensions::hauteurTrottoir);
	Quad qbordureh = qtrottoirh.inset(E,15);

	addGPUQuad(Quad(c[SE], qtrottoir[SE], qtrottoir[NE], c[NE]), Couleurs::route);
	addGPUQuad(qtrottoir[NE], qtrottoir[SE], qtrottoirh[SE], qtrottoirh[NE], Couleurs::bordureTrottoir);
	addGPUQuad(qtrottoirh[NE], qtrottoirh[SE], qbordureh[SE], qbordureh[NE], Couleurs::bordureTrottoir);
	addGPUQuad(qbordureh, Couleurs::trottoir);
}
