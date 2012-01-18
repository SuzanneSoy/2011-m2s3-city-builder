#include "all_includes.hh"

int main() {
	// Générer une tile de base
	std::cout << "Initial seed = " << Chose::initialSeed << std::endl;
	float size = 500 * 100;
	Vertex ne(size, size, 0);
	Vertex se(size, 0, 0);
	Vertex sw(0, 0, 0);
	Vertex nw(0, size, 0);
	Chose* c = new QuartierQuad(Quad(ne, se, sw, nw));
	c->triangulation();
	c->updateAABB();

	new View(c);
	return 0;
}
