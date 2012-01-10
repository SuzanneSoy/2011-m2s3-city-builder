#include "all_includes.hh"

TrottoirQuadNormal::TrottoirQuadNormal(Quad _c, float _height) : Chose(), c(_c), height(_height) {
}

void TrottoirQuadNormal::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height));
}

void TrottoirQuadNormal::triangulation() {
	Quad ch = c + Vertex(0,0,height);
	Quad bordureh = ch.inset(E,15);

	addGPUQuad(c[NE], c[SE], ch[SE], ch[NE], 0xAA, 0xAA, 0xAA);
	addGPUQuad(ch[NE], ch[SE], bordureh[SE], bordureh[NE], 0xAA, 0xAA, 0xAA);
	addGPUQuad(bordureh, 0x66, 0x66, 0x66);
}
