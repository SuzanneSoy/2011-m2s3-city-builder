#include "all_includes.hh"

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	// Générer une tile de base
	if(argc > 1)
        Chose::initialSeed = (unsigned int) atoi(argv[1]);

	std::cout << "Initial seed = " << Chose::initialSeed << std::endl;
	float size = 20000 * 100;
	Vertex ne(+size/2.f, +size/2.f, 0);
	Vertex se(+size/2.f, -size/2.f, 0);
	Vertex sw(-size/2.f, -size/2.f, 0);
	Vertex nw(-size/2.f, +size/2.f, 0);

	Chose* c = new QuartierQuad(Quad(ne, se, sw, nw));
	c->triangulation();
	c->updateAABB();

	new View(c);
	return 0;
}
