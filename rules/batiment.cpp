#include "all_includes.hh"

Batiment::Batiment(Vertex ne, Vertex sw) : Chose(), ne(ne), sw(sw) {
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
	
	// abcd sont les quatre coins du bâtiment.
	Vertex a = this->ne;
	Vertex b = Vertex(this->ne.x, this->sw.y, 0);
	Vertex c = Vertex(this->sw.x, this->ne.y, 0);
	Vertex d = this->sw;

	int h = hashInRange(seed,0,4,8);
	Vertex ah = a + Vertex(0,0,h);
	Vertex bh = b + Vertex(0,0,h);
	Vertex ch = c + Vertex(0,0,h);
	Vertex dh = d + Vertex(0,0,h);
	Vertex toit = (ah + bh + ch + dh) / 4 + Vertex(0,0,h/2);

	// 4 Murs
	addTriangle(new Triangle(a,bh,ah,0xf1,0xe3,0xad)); addTriangle(new Triangle(a,b,bh,0xf1,0xe3,0xad)); // a-b-bh-ah
	addTriangle(new Triangle(b,dh,bh,0xf1,0xe3,0xad)); addTriangle(new Triangle(b,d,dh,0xf1,0xe3,0xad)); // b-d-dh-bh
	addTriangle(new Triangle(d,ch,dh,0xf1,0xe3,0xad)); addTriangle(new Triangle(d,c,ch,0xf1,0xe3,0xad)); // d-c-ch-dh
	addTriangle(new Triangle(c,ah,ch,0xf1,0xe3,0xad)); addTriangle(new Triangle(c,a,ah,0xf1,0xe3,0xad)); // c-a-ah-ch

	// 1 Toit
	addTriangle(new Triangle(ah,toit,bh,0x8a,0x48,0x3c));
	addTriangle(new Triangle(bh,toit,dh,0x8a,0x48,0x3c));
	addTriangle(new Triangle(dh,toit,ch,0x8a,0x48,0x3c));
	addTriangle(new Triangle(ch,toit,ah,0x8a,0x48,0x3c));
}

std::ostream& operator<<(std::ostream& os, const Batiment* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Batiment& r) {
	return os << "Batiment " << r.ne << "-" << r.sw;
}
