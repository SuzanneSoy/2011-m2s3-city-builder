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
        addChild(new BatimentQuadMaisonPont(c,800));
	} else {
        float th = 20;        // Terrain height.
        Quad qtrottoir = c.insetNESW(250);
        Quad qmaison = qtrottoir.insetNESW(140);

        for (int i = 0; i <4; i++) {
        	addChild(new RouteQuadChaussee(Quad(c[NE+i],c[SE+i],qtrottoir[SE+i],qtrottoir[NE+i])));
        	addChild(new TrottoirQuadNormal(Quad(qtrottoir[NE+i],qtrottoir[SE+i],qmaison[SE+i],qmaison[NE+i]),th));
        }

        Quad qhmaison = qmaison + Vertex(0,0,th);
        addChild(new BatimentQuadJardin(qhmaison));

        addChild(new BatimentQuadMaison(qhmaison.inset(N,400)));
	}
	return true;
}

void BatimentQuad::triangulation() {
	triangles.reserve(12);

	float h = floatInRange(seed,1,minHeight,maxHeight);
	float htoit = floatInRange(seed,2,minHeight/2,maxHeight/2);

    addGPUOcto(c, c + Vertex(0,0,h + htoit), 0xFF, 0xFF, 0x00);
}
