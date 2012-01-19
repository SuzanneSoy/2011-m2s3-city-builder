#include "all_includes.hh"

TrottoirQuad::TrottoirQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void TrottoirQuad::getBoundingBoxPoints() {
	addBBPoints(c, Dimensions::hauteurTrottoir);
}

void TrottoirQuad::triangulation() {
	Quad ch = c.offsetNormal(Dimensions::hauteurTrottoir);
	Quad bordureh = ch.inset(E,15);

	addGPUQuad(c[NE], c[SE], ch[SE], ch[NE], Couleurs::bordureTrottoir);
	addGPUQuad(ch[NE], ch[SE], bordureh[SE], bordureh[NE], Couleurs::bordureTrottoir);
	addGPUQuad(bordureh, Couleurs::trottoir);
}

RouteQuad::RouteQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void RouteQuad::getBoundingBoxPoints() {
	addBBPoints(c);
}

void RouteQuad::triangulation() {
	addGPUQuad(c, Couleurs::route);
}
