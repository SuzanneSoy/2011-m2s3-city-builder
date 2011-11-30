#include "all_includes.hh"

Batiment::Batiment(Vertex ne, Vertex se, Vertex sw, Vertex nw) : Chose(), ne(ne), se(se), sw(sw), nw(nw) {
	addEntropy(ne, sw);
	triangulation();
}

int Batiment::width() { return this->ne.x - this->sw.x; }

int Batiment::height() { return this->ne.y - this->sw.y; }

bool Batiment::subdivide() {
	// TODO : rien ?
	return false;
}

void Batiment::triangulation() {
	triangles.reserve(12);
	
	int h = hashInRange(seed,0,4,8);
	Vertex neh = ne + Vertex(0,0,h);
	Vertex seh = se + Vertex(0,0,h);
	Vertex nwh = nw + Vertex(0,0,h);
	Vertex swh = sw + Vertex(0,0,h);
	Vertex toit = (neh + seh + nwh + swh) / 4 + Vertex(0,0,h/2);

	// 4 Murs
	addTriangle(new Triangle(neh,seh,ne,0xf1,0xe3,0xad)); addTriangle(new Triangle(seh,se,ne,0xf1,0xe3,0xad)); // ne-se-seh-neh
	addTriangle(new Triangle(seh,swh,se,0xf1,0xe3,0xad)); addTriangle(new Triangle(swh,sw,se,0xf1,0xe3,0xad)); // se-sw-swh-seh
	addTriangle(new Triangle(swh,nwh,sw,0xf1,0xe3,0xad)); addTriangle(new Triangle(nwh,nw,sw,0xf1,0xe3,0xad)); // sw-nw-nwh-swh
	addTriangle(new Triangle(nwh,neh,nw,0xf1,0xe3,0xad)); addTriangle(new Triangle(neh,ne,nw,0xf1,0xe3,0xad)); // nw-ne-neh-nwh

	// 1 Toit
	addTriangle(new Triangle(neh,toit,seh,0x8a,0x48,0x3c));
	addTriangle(new Triangle(seh,toit,swh,0x8a,0x48,0x3c));
	addTriangle(new Triangle(swh,toit,nwh,0x8a,0x48,0x3c));
	addTriangle(new Triangle(nwh,toit,neh,0x8a,0x48,0x3c));
}
