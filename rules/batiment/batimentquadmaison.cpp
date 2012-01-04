#include "all_includes.hh"

BatimentQuadMaison::BatimentQuadMaison(Quad c) : Chose(), c(c) {
	addEntropy(c);
}

void BatimentQuadMaison::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
}

void BatimentQuadMaison::triangulation() {
	triangles.reserve(12);

	int h = hashInRange(seed,0,minHeight,maxHeight);
	int htoit = hashInRange(seed,0,minHeight/2,maxHeight/2);
	Quad ch = c + Vertex(0,0,h);
	Vertex toit = (ch[NE] + ch[SE] + ch[SW] + ch[NW]) / 4 + Vertex(0,0,htoit);

	// 4 Murs
	addQuad(ch[NE],ch[SE],c[SE],c[NE],0xf1,0xe3,0xad);
	addQuad(ch[SE],ch[SW],c[SW],c[SE],0xf1,0xe3,0xad);
	addQuad(ch[SW],ch[NW],c[NW],c[SW],0xf1,0xe3,0xad);
	addQuad(ch[NW],ch[NE],c[NE],c[NW],0xf1,0xe3,0xad);

	// 1 Toit
	addTriangle(new GPUTriangle(ch[NE],toit,ch[SE],0x96,0x16,0x18));
	addTriangle(new GPUTriangle(ch[SE],toit,ch[SW],0x96,0x16,0x18));
	addTriangle(new GPUTriangle(ch[SW],toit,ch[NW],0x96,0x16,0x18));
	addTriangle(new GPUTriangle(ch[NW],toit,ch[NE],0x96,0x16,0x18));
}
