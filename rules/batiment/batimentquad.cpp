#include "all_includes.hh"

BatimentQuad::BatimentQuad(Quad c, Cardinal entry) : Chose(), c(c), entry(entry) {
	addEntropy(c);
	addEntropy(entry);
}

void BatimentQuad::getBoundingBoxPoints() {
	addBBPoints(c);
	addBBPoints(c + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
}

bool BatimentQuad::split() {
	if(proba(seed, 0, 1, 10)) {
        Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);
        // TODO ajouter une classe surface.
        //addQuad(c[SE],c[SW],c[NW],c[NE],0xDD,0xDD,0xDD);
        addChild(new BatimentQuadMaisonPont(q,800));
	} else {
        int th = 20;        // Terrain height.
        Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);
        q.offset(N,-140);
        q.offset(E,-140);
        q.offset(S,-140);
        q.offset(W,-140);

        addChild(new TrottoirQuadNormal(Quad(c[NE],c[SE],q[SE],q[NE]),th));
        addChild(new TrottoirQuadNormal(Quad(c[SE],c[SW],q[SW],q[SE]),th));
        addChild(new TrottoirQuadNormal(Quad(c[SW],c[NW],q[NW],q[SW]),th));
        addChild(new TrottoirQuadNormal(Quad(c[NW],c[NE],q[NE],q[NW]),th));

        Quad qh = q + Vertex(0,0,th);
        addChild(new BatimentQuadJardin(qh));

        qh.offset(this->entry,-400);
        addChild(new BatimentQuadMaison(qh));
	}
	return true;
}

void BatimentQuad::triangulation() {
	triangles.reserve(12);

	int h = hashInRange(seed,1,minHeight,maxHeight);
	int htoit = hashInRange(seed,2,minHeight/2,maxHeight/2);
	h += htoit;

    addGPUOcto(c, c + Vertex(0,0,h), 0xFF, 0xFF, 0x00);
}
