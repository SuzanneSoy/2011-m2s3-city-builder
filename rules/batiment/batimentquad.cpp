#include "all_includes.hh"

BatimentQuad::BatimentQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw, Cardinal entry) : Chose() {
	addEntropy(ne, se, sw, nw);
	this->entry = entry;
	c[NE] = ne;//-lctr;
	c[SE] = se;//-lctr;
    c[SW] = sw;//-lctr;
    c[NW] = nw;//-lctr;
}

BatimentQuad::~BatimentQuad() {
    children.clear();
    triangles.clear();
}

void BatimentQuad::getBoundingBoxPoints() {
	addBBPoint(c[NE]);
	addBBPoint(c[SE]);
	addBBPoint(c[SW]);
	addBBPoint(c[NW]);
	addBBPoint(c[NE] + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
	addBBPoint(c[SE] + Vertex(0,0,maxHeight + maxHeight/2));
	addBBPoint(c[SW] + Vertex(0,0,maxHeight + maxHeight/2));
	addBBPoint(c[NW] + Vertex(0,0,maxHeight + maxHeight/2));
}

bool BatimentQuad::split() {
	int rand = this->seed % 20; // TODO : utiliser les fonctions random in range & co.

	if(rand <= 1) {
        Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);
        // TODO ajouter une classe surface.
        //addQuad(c[SE],c[SW],c[NW],c[NE],0xDD,0xDD,0xDD);
        addChild(new BatimentQuadMaisonPont(q.c[0],q.c[1],q.c[2],q.c[3],800));
	}
	else {
        int th = 20;        // Terrain height.
        Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);
        th = th;
        q.offset(N,-140);
        q.offset(E,-140);
        q.offset(S,-140);
        q.offset(W,-140);

        addChild(new TrottoirQuadNormal(c[NE],c[SE],q.c[1],q.c[0],th,E));
        addChild(new TrottoirQuadNormal(c[SE],c[SW],q.c[2],q.c[1],th,E));
        addChild(new TrottoirQuadNormal(c[SW],c[NW],q.c[3],q.c[2],th,E));
        addChild(new TrottoirQuadNormal(c[NW],c[NE],q.c[0],q.c[3],th,E));

        q.c[0] = q.c[0] + Vertex(0,0,th);
        q.c[1] = q.c[1] + Vertex(0,0,th);
        q.c[2] = q.c[2] + Vertex(0,0,th);
        q.c[3] = q.c[3] + Vertex(0,0,th);

        addChild(new BatimentQuadJardin(q.c[0],q.c[1],q.c[2],q.c[3]));

        q.offset(this->entry,-400);

        addChild(new BatimentQuadMaison(q.c[0],q.c[1],q.c[2],q.c[3]));
	}
	return true;
}

void BatimentQuad::triangulation() {
	triangles.reserve(12);

	int h = hashInRange(seed,0,minHeight,maxHeight);
	int htoit = hashInRange(seed,0,minHeight/2,maxHeight/2);
	h += htoit;
	Vertex neh = c[NE] + Vertex(0,0,h);
	Vertex seh = c[SE] + Vertex(0,0,h);
	Vertex nwh = c[NW] + Vertex(0,0,h);
	Vertex swh = c[SW] + Vertex(0,0,h);

    addOcto(c[NE],c[SE],c[SW],c[NW],neh,seh,swh,nwh,0xFF,0xFF,0x00);
}
