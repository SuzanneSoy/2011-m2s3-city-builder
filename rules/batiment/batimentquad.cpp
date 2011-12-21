#include "all_includes.hh"

BatimentQuad::BatimentQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw, Cardinal entry) : Chose() {
	addEntropy(ne, se, sw, nw);
	this->entry = entry;
	lctr = (ne + se + sw + nw) / 4;
    corner[NE] = ne;//-lctr;
	corner[SE] = se;//-lctr;
    corner[SW] = sw;//-lctr;
    corner[NW] = nw;//-lctr;
}

BatimentQuad::~BatimentQuad() {
    children.clear();
    triangles.clear();
}

void BatimentQuad::getBoundingBoxPoints() {
	addBBPoint(corner[NE]);
	addBBPoint(corner[SE]);
	addBBPoint(corner[SW]);
	addBBPoint(corner[NW]);
	addBBPoint(corner[NE] + Vertex(0,0,maxHeight + maxHeight/2)); // TODO
	addBBPoint(corner[SE] + Vertex(0,0,maxHeight + maxHeight/2));
	addBBPoint(corner[SW] + Vertex(0,0,maxHeight + maxHeight/2));
	addBBPoint(corner[NW] + Vertex(0,0,maxHeight + maxHeight/2));
}

bool BatimentQuad::split() {
	int th = 20; // Terrain height.
	Quad q = Quad(corner[NE],corner[SE],corner[SW],corner[NW]);
	q.offset(N,-140);
	q.offset(E,-140);
	q.offset(S,-140);
	q.offset(W,-140);

	addChild(new TrottoirQuadNormal(/*lctr+*/corner[NE],/*lctr+*/corner[SE],/*lctr+*/q.corner[1],/*lctr+*/q.corner[0],th,E));
    addChild(new TrottoirQuadNormal(/*lctr+*/corner[SE],/*lctr+*/corner[SW],/*lctr+*/q.corner[2],/*lctr+*/q.corner[1],th,E));
    addChild(new TrottoirQuadNormal(/*lctr+*/corner[SW],/*lctr+*/corner[NW],/*lctr+*/q.corner[3],/*lctr+*/q.corner[2],th,E));
    addChild(new TrottoirQuadNormal(/*lctr+*/corner[NW],/*lctr+*/corner[NE],/*lctr+*/q.corner[0],/*lctr+*/q.corner[3],th,E));

    q.corner[0] = q.corner[0] + Vertex(0,0,th);
    q.corner[1] = q.corner[1] + Vertex(0,0,th);
    q.corner[2] = q.corner[2] + Vertex(0,0,th);
    q.corner[3] = q.corner[3] + Vertex(0,0,th);

    addChild(new BatimentQuadJardin(/*lctr+*/q.corner[0],/*lctr+*/q.corner[1],/*lctr+*/q.corner[2],/*lctr+*/q.corner[3]));

    q.offset(this->entry,-400);

	addChild(new BatimentQuadMaison(/*lctr+*/q.corner[0],/*lctr+*/q.corner[1],/*lctr+*/q.corner[2],/*lctr+*/q.corner[3]));
	return true;
}

void BatimentQuad::triangulation() {
	triangles.reserve(12);

	int h = hashInRange(seed,0,minHeight,maxHeight);
	int htoit = hashInRange(seed,0,minHeight/2,maxHeight/2);
	Vertex neh = corner[NE] + Vertex(0,0,h);
	Vertex seh = corner[SE] + Vertex(0,0,h);
	Vertex nwh = corner[NW] + Vertex(0,0,h);
	Vertex swh = corner[SW] + Vertex(0,0,h);
	Vertex toit = (neh + seh + nwh + swh) / 4 + Vertex(0,0,htoit);

	// 4 Murs
	addTriangle(new Triangle(neh,seh,corner[NE],0xf1,0xe3,0xad)); addTriangle(new Triangle(seh,corner[SE],corner[NE],0xf1,0xe3,0xad)); // ne-se-seh-neh
	addTriangle(new Triangle(seh,swh,corner[SE],0xf1,0xe3,0xad)); addTriangle(new Triangle(swh,corner[SW],corner[SE],0xf1,0xe3,0xad)); // se-sw-swh-seh
	addTriangle(new Triangle(swh,nwh,corner[SW],0xf1,0xe3,0xad)); addTriangle(new Triangle(nwh,corner[NW],corner[SW],0xf1,0xe3,0xad)); // sw-nw-nwh-swh
	addTriangle(new Triangle(nwh,neh,corner[NW],0xf1,0xe3,0xad)); addTriangle(new Triangle(neh,corner[NE],corner[NW],0xf1,0xe3,0xad)); // nw-ne-neh-nwh

	// 1 Toit
	addTriangle(new Triangle(neh,toit,seh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(seh,toit,swh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(swh,toit,nwh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(nwh,toit,neh,0x9a,0x48,0x3c));
}
