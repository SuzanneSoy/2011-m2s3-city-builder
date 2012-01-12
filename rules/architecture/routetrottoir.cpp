#include "all_includes.hh"

TrottoirQuad::TrottoirQuad(Quad _c, float _height) : Chose(), c(_c), height(_height) {
	addEntropy(c);
	addEntropy(height);
}

void TrottoirQuad::getBoundingBoxPoints() {
	addBBPoints(c, height);
}

void TrottoirQuad::triangulation() {
	Quad ch = c.offsetNormal(height);
	Quad bordureh = ch.inset(E,15);

	addGPUQuad(c[NE], c[SE], ch[SE], ch[NE], 0xAA, 0xAA, 0xAA);
	addGPUQuad(ch[NE], ch[SE], bordureh[SE], bordureh[NE], 0xAA, 0xAA, 0xAA);
	addGPUQuad(bordureh, 0x66, 0x66, 0x66);
}

RouteQuad::RouteQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void RouteQuad::getBoundingBoxPoints() {
	// TODO : quelle hauteur mettre pour la route ? Il faut mettre 0 et ajuster le
	// calcul des splitBox et mergeBox pour prendre en compre la somme des surfaces
	// potentiellement visibles de l'objet.
	addBBPoints(c, 1000);
}

void RouteQuad::triangulation() {
	addGPUQuad(c, 0x36, 0x36, 0x36);
}
