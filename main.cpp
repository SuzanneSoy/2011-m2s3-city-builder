#include "all_includes.hh"

// TODO : créer les routes dans les bâtiments

int main() {
	// Générer une tile de base
	std::cout << "Initial seed = " << Chose::initialSeed << std::endl;
	float size = 20000;
	Vertex ne(size, size, 0);
	Vertex se(size, 0, 0);
	Vertex sw(0, 0, 0);
	Vertex nw(0, size, 0);
	Chose* c = QuartierQuad::factory(Chose::initialSeed, 0, Quad(ne, se, sw, nw));
	c->triangulation();
	c->updateAABB();

	//std::cout << Triangle(se, sw, nw).surface() << std::endl;
	std::cout << Quad(Vertex(10,10,0), Vertex(10,0,0), Vertex(0,0,0), Vertex(0,10,0)).surface() << std::endl;

	//new View(c);
	return 0;
}
