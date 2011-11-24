#include "all_includes.hh"

Batiment::Batiment(Vertex ne, Vertex sw) : ne(ne), sw(sw) {
	std::cout << this << std::endl;
}

int Batiment::width() { return this->ne.x - this->sw.x; }

int Batiment::height() { return this->ne.y - this->sw.y; }

void Batiment::subdivide() {
	// TODO : rien ?
}

void Batiment::triangulation() {
	// abcd sont les quatre coins du bâtiment.
	Vertex a = this->ne;
	Vertex b = Vertex(this->ne.x, this->sw.y, 0);
	Vertex c = this->sw;
	Vertex d = Vertex(this->sw.x, this->ne.y, 0);
	
	int h = 6;
	Vertex ah = a + Vertex(0,0,h);
	Vertex bh = b + Vertex(0,0,h);
	Vertex ch = c + Vertex(0,0,h);
	Vertex dh = d + Vertex(0,0,h);
	Vertex toit = (ah + bh + ch + dh) / 4 + Vertex(0,0,h/5);

	// 4 Murs
	new Triangle(a,bh,ah); new Triangle(a,b,bh); // a-b-bh-ah
	new Triangle(b,dh,bh); new Triangle(b,d,dh); // b-d-dh-bh
	new Triangle(d,ch,dh); new Triangle(d,c,ch); // d-c-ch-dh
	new Triangle(c,ah,ch); new Triangle(c,a,ah); // c-a-ah-ch

	// 1 Toit
	new Triangle(ah,toit,bh);
	new Triangle(bh,toit,dh);
	new Triangle(dh,toit,ch);
	new Triangle(ch,toit,ah);
}

std::ostream& operator<<(std::ostream& os, const Batiment* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Batiment& r) {
	return os << "Batiment " << r.ne << "-" << r.sw;
}
