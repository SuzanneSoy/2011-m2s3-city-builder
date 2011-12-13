#include "all_includes.hh"

BatimentQuad::BatimentQuad(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
	addEntropy(ne, se, sw, nw);
	triangulation();
}

int BatimentQuad::width() { return this->ne.x - this->sw.x; }

int BatimentQuad::height() { return this->ne.y - this->sw.y; }

bool BatimentQuad::subdivide() {
    factory(1,1,ne,se,sw,nw);
	return true;
}

Chose* BatimentQuad::factory(int seed, int n, Vertex ne, Vertex se, Vertex sw, Vertex nw) {
	//return false;
	Quad q = Quad(ne,se,sw,nw);
	seed = seed;
	n = n;
	q.offset(N,-140);
	q.offset(E,-140);
	q.offset(S,-140);
	q.offset(W,-140);

	addChild(new BatimentQuadMaison(q.corner[0],q.corner[1],q.corner[2],q.corner[3]));
    addChild(new TrottoirQuadNormal(ne,se,q.corner[1],q.corner[0],20,E));
    addChild(new TrottoirQuadNormal(se,sw,q.corner[2],q.corner[1],20,E));
    addChild(new TrottoirQuadNormal(sw,nw,q.corner[3],q.corner[2],20,E));
    addChild(new TrottoirQuadNormal(nw,ne,q.corner[0],q.corner[3],20,E));
	return NULL;	// pour compilation, à virer.
}

void BatimentQuad::triangulation() {
	triangles.reserve(12);

	int h = hashInRange(seed,0,minHeight,maxHeight);
	int htoit = hashInRange(seed,0,minHeight/2,maxHeight/2);
	Vertex neh = ne + Vertex(0,0,h);
	Vertex seh = se + Vertex(0,0,h);
	Vertex nwh = nw + Vertex(0,0,h);
	Vertex swh = sw + Vertex(0,0,h);
	Vertex toit = (neh + seh + nwh + swh) / 4 + Vertex(0,0,htoit);

	// 4 Murs
	addTriangle(new Triangle(neh,seh,ne,0xf1,0xe3,0xad)); addTriangle(new Triangle(seh,se,ne,0xf1,0xe3,0xad)); // ne-se-seh-neh
	addTriangle(new Triangle(seh,swh,se,0xf1,0xe3,0xad)); addTriangle(new Triangle(swh,sw,se,0xf1,0xe3,0xad)); // se-sw-swh-seh
	addTriangle(new Triangle(swh,nwh,sw,0xf1,0xe3,0xad)); addTriangle(new Triangle(nwh,nw,sw,0xf1,0xe3,0xad)); // sw-nw-nwh-swh
	addTriangle(new Triangle(nwh,neh,nw,0xf1,0xe3,0xad)); addTriangle(new Triangle(neh,ne,nw,0xf1,0xe3,0xad)); // nw-ne-neh-nwh

	// 1 Toit
	addTriangle(new Triangle(neh,toit,seh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(seh,toit,swh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(swh,toit,nwh,0x9a,0x48,0x3c));
	addTriangle(new Triangle(nwh,toit,neh,0x9a,0x48,0x3c));
}
