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
	addTriangle(new Triangle(a,bh,ah)); addTriangle(new Triangle(a,b,bh)); // a-b-bh-ah
	addTriangle(new Triangle(b,dh,bh)); addTriangle(new Triangle(b,d,dh)); // b-d-dh-bh
	addTriangle(new Triangle(d,ch,dh)); addTriangle(new Triangle(d,c,ch)); // d-c-ch-dh
	addTriangle(new Triangle(c,ah,ch)); addTriangle(new Triangle(c,a,ah)); // c-a-ah-ch

	// 1 Toit
	addTriangle(new Triangle(ah,toit,bh));
	addTriangle(new Triangle(bh,toit,dh));
	addTriangle(new Triangle(dh,toit,ch));
	addTriangle(new Triangle(ch,toit,ah));
}

std::ostream& operator<<(std::ostream& os, const Batiment* r) {
	return os << *r;
}

std::ostream& operator<<(std::ostream& os, const Batiment& r) {
	return os << "Batiment " << r.ne << "-" << r.sw;
}
