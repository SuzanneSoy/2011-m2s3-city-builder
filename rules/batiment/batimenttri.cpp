#include "all_includes.hh"

BatimentTri::BatimentTri(Triangle _c) : Chose(), c(_c) {
	addEntropy(c);
}

void BatimentTri::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
}

bool BatimentTri::split() {
	return false;
	// if(proba(seed, 0, 1, 10)) {
    //     Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);
    //     // TODO ajouter une classe surface.
    //     //addQuad(c[SE],c[SW],c[NW],c[NE],0xDD,0xDD,0xDD);
    //     addChild(new BatimentQuadMaisonPont(q,800));
	// } else {
	// 	int th = 20;        // Terrain height.
	// 	Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);
	// 	q.offset(N,-140);
	// 	q.offset(E,-140);
	// 	q.offset(S,-140);
	// 	q.offset(W,-140);

	// 	addChild(new TrottoirQuadNormal(Quad(c[NE],c[SE],q[SE],q[NE]),th,E));
	// 	addChild(new TrottoirQuadNormal(Quad(c[SE],c[SW],q[SW],q[SE]),th,E));
	// 	addChild(new TrottoirQuadNormal(Quad(c[SW],c[NW],q[NW],q[SW]),th,E));
	// 	addChild(new TrottoirQuadNormal(Quad(c[NW],c[NE],q[NE],q[NW]),th,E));

	// 	Quad qh = q + Vertex(0,0,th);
	// 	addChild(new BatimentQuadJardin(qh));

	// 	qh.offset(this->entry,-400);
	// 	addChild(new BatimentQuadMaison(qh));
	// }
	// return true;
}

void BatimentTri::triangulation() {
	float h = floatInRange(seed,1,minHeight,maxHeight);
	// float htoit = hashInRange(seed,2,minHeight/2,maxHeight/2);

    // addGPUOcto(c, c + Vertex(0,0,h + htoit), 0xFF, 0xFF, 0x00);
	Triangle ch = c + Vertex(0,0,h);
	addGPUTriangle(c[LEFT], c[TOP], c[RIGHT], 0xFF, 0xFF, 0x00);
	addGPUTriangle(ch[LEFT], ch[TOP], ch[RIGHT], 0xFF, 0xFF, 0x00);
	for (int i = 0; i < 3; i++)
		addGPUQuad(c[LEFT+i], c[TOP+i], ch[TOP+i], ch[LEFT+i], 0xFF, 0xFF, 0x00);
}
