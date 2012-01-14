#include "all_includes.hh"

BatimentQuad::BatimentQuad(Quad _c) : Chose(), c(_c) {
	addEntropy(c);
}

void BatimentQuad::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
}

bool BatimentQuad::split() {
	if(proba(seed, 0, 1, 10)) {
        addChild(new BatimentQuadMaisonPont(c,3));
	} else {
        addChild(new BatimentQuadJardin(c));

        addChild(new BatimentQuadMaison(c.inset(N,400)));
	}
	return true;
}

void BatimentQuad::triangulation() {
	triangles.reserve(12);

	float h = floatInRange(seed,1,minHeight,maxHeight);
	float htoit = floatInRange(seed,2,minHeight/2,maxHeight/2);

    addGPUOcto(c, c + Vertex(0,0,h + htoit), 0xFFFFFF);
}
