#include "all_includes.hh"

TrottoirQuadNormal::TrottoirQuadNormal(Quad c, int height) : Chose(), c(c), height(height) {
}

void TrottoirQuadNormal::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,height));
}

void TrottoirQuadNormal::triangulation() {
	Quad ch = c + Vertex(0,0,height);
	Quad bordureh = ch;
	bordureh.offset(E,-15);

	addGPUQuad(c[NE], c[SE], ch[SE], ch[NE], 0xAA, 0xAA, 0xAA);
	addGPUQuad(ch[NE], ch[SE], bordureh[SE], bordureh[NE], 0xAA, 0xAA, 0xAA);
	addGPUQuad(bordureh, 0x66, 0x66, 0x66);
}
