#include "all_includes.hh"

BatimentQuadMaison::BatimentQuadMaison(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void BatimentQuadMaison::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
}

bool BatimentQuadMaison::split() {
    float h = floatInRange(seed,0,minHeight,maxHeight);
	float htoit = floatInRange(seed,0,minHeight/2,maxHeight/2);
	Quad ch = c + Vertex(0,0,h);
	Vertex toit = (ch[NE] + ch[SE] + ch[SW] + ch[NW]) / 4 + Vertex(0,0,htoit);

	addChild(new BatimentQuadBlock(c,ch));
	addChild(new BatimentQuadToit(ch,1));
    return true;
}

void BatimentQuadMaison::triangulation() {
	triangles.reserve(12);

	float h = floatInRange(seed,0,minHeight,maxHeight);
	float htoit = floatInRange(seed,0,minHeight/2,maxHeight/2);
	Quad ch = c + Vertex(0,0,h);
	Vertex toit = (ch[NE] + ch[SE] + ch[SW] + ch[NW]) / 4 + Vertex(0,0,htoit);

    addGPUOcto(c,ch,0xf1,0xe3,0xad);

	for (int i = 0; i < 4; i++) {
		addGPUTriangle(ch[SE+i],toit,ch[NE+i],0x96,0x16,0x18);
	}
}
