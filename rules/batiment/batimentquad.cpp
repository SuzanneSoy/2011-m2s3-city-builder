#include "all_includes.hh"

BatimentQuad::BatimentQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw, Cardinal entry) : Chose() {
	addEntropy(ne, se, sw, nw);
	this->entry = entry;
	lctr = (ne + se + sw + nw) / 4;
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

	if(rand <= 2) {
        Quad q = Quad(c[NE],c[SE],c[SW],c[NW]).makeParallelogram();
        addChild(new BatimentQuadMaisonPont(q.corner[0],q.corner[1],q.corner[2],q.corner[3],800));
	}
	else if(rand <= 15) {
        int th = 20;        // Terrain height.
        Quad q = Quad(c[NE],c[SE],c[SW],c[NW]);
        th = th;
        q.offset(N,-140);
        q.offset(E,-140);
        q.offset(S,-140);
        q.offset(W,-140);

        addChild(new TrottoirQuadNormal(c[NE],c[SE],q.corner[1],q.corner[0],th,E));
        addChild(new TrottoirQuadNormal(c[SE],c[SW],q.corner[2],q.corner[1],th,E));
        addChild(new TrottoirQuadNormal(c[SW],c[NW],q.corner[3],q.corner[2],th,E));
        addChild(new TrottoirQuadNormal(c[NW],c[NE],q.corner[0],q.corner[3],th,E));

        q.corner[0] = q.corner[0] + Vertex(0,0,th);
        q.corner[1] = q.corner[1] + Vertex(0,0,th);
        q.corner[2] = q.corner[2] + Vertex(0,0,th);
        q.corner[3] = q.corner[3] + Vertex(0,0,th);

        addChild(new BatimentQuadJardin(q.corner[0],q.corner[1],q.corner[2],q.corner[3]));

        q.offset(this->entry,-400);

        addChild(new BatimentQuadMaison(q.corner[0],q.corner[1],q.corner[2],q.corner[3]));
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
