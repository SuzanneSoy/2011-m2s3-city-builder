#include "all_includes.hh"

int main(int argc, char* argv[]) {
	// Générer une tile de base
	if(argc > 1)
        Chose::initialSeed = (unsigned int) atoi(argv[1]);

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
